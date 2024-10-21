LIBSEH - a Windows SEH compatibility library for GCC.
(C) 2008 Tom Bramer ( tjb at postpro dot net )

This is possibly alpha grade code.  But then again, it might work very well.  It seems to work 
in my limited testing so far.

The Linux/cygwin implementation is not complete and will not pass all tests.

About LIBSEH:
LIBSEH is a compatibility layer that allows one to utilize the Structured 
Exception Handling facility found in Windows within GCC for Windows (MINGW32, CYGWIN).  
In other compilers, SEH is built into the compiler as a language extension.  In other 
words, this syntax is not standard C or C++, where standard in this case includes any 
ANSI standard.  Usually, support for this feature is implemented through __try, __except, 
and __finally compound statements.  Here is an example:


#include <windows.h>
#include <stdio.h>

int ExceptionFilter(unsigned int code, unsigned int excToFilter)
{
    if(code == excToFilter) return EXCEPTION_EXECUTE_HANDLER;
    else return EXCEPTION_CONTINUE_SEARCH;
}

int main()
{
    int x = 0;
    int y = 4;
    __try 
    {
        y /= x;
    }
    __except(ExceptionFilter(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO)) 
    {
        printf("Divide by zero exception.\n");
    }

    return 0;
}


This is only supported in Microsoft C/C++ and Digital Mars C/C++.  They are not 
standard language constructs.

LIBSEH allows programs intended for GCC to utilize this feature, with a high degree 
of source-level compatibility and minimal existing code changes.  To modify the 
above program in order to compile it on GCC with LIBSEH, two extra lines must
be added:


#include <windows.h>
#include <stdio.h>
#include <seh.h>       /***** LINE 1 of additional code *****/

int ExceptionFilter(unsigned int code, unsigned int excToFilter)
{
    if(code == excToFilter) return EXCEPTION_EXECUTE_HANDLER;
    else return EXCEPTION_CONTINUE_SEARCH;
}

int main()
{
    int x = 0;
    int y = 4;
    __try 
    {
        y /= x;
    }
    __except(ExceptionFilter(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO)) 
    {
        printf("Divide by zero exception.\n");
    }
    __end_except       /***** LINE 2 of additional code *****/

    return 0;
}


Not very much to it, really.  The seh.h header includes other headers, and when preprocessed 
under Microsoft C/C++ and Digital Mars C/C++ (untested), the __end_except is defined as a 
no-op.  It does have meaning though for GCC, and the program will not compile without it 
(and since the above are preprocessor macros, strange compiler errors will result, so keep 
this in mind when something doesn't compile).

All of this allows the same source to be compiled on GCC and Microsoft C/C++ (and most likely,
Digital Mars C/C++).

The library also supports the __try/__finally combination:  

int main()
{
    int x = 0;
    int y = 4;
    __try 
    {
        __try {
            y /= x;
        }
        __finally {
            printf("Leaving __try/__finally compound statement.\n");
        }
        __end_finally          /****** NOTE THE __end_finally, also required ******/
    }
    __except(ExceptionFilter(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO)) 
    {
        printf("Divide by zero exception.\n");
    }
    __end_except

    return 0;
}

The __finally block will be called if an exception is raised, and the exception is handled 
in a block farther up on the stack.  It's also called if no exception occurs.  


***********************************************************************************************
        
KNOWN DIFFERENCES BETWEEN LIBSEH AND BUILT IN IMPLEMENTATIONS OF SEH:

Yes, it's true.  LIBSEH does not have the exact same behavior as builtin SEH in Microsoft C/C++.
Here are some of the currently known differences (and I could be incorrect, as I haven't tested
all of these):

These differences only affect when LIBSEH is really being used, like when using GCC.

* __finally in LIBSEH does not handle currently C++ exceptions.  If code leaves the __try block 
  other than leaving the __try block (finishing execution) or because of a raised SEH exception, the 
  __finally block will not be executed.  This applies to all other ways of exiting the __try block,
  such as return and goto.

* The order of execution of filter expressions and __finally blocks is slightly different.  With
  Microsoft C/C++, I don't believe the compiler executes any __finally blocks until an exception
  handler is found (in this case, this means an __except block that will trap the exception).  
  With LIBSEH, each block is executed in order up the stack, so in the case of:
  
  __try {
      __try {
          *(int*)0 = 4;
      }
      __finally {
          /* Do something */
      }
      __end_finally
  }
  __except(filter_expr) {
      /* Do something */
  }
  __end_except

  The __finally block will be executed before the __except expression is evaluated, because the __finally is
  further down on the stack.  

* GetExceptionCode/GetExceptionInformation are not required to be called within the __except 
  expression for LIBSEH.  This is due to how the exception information is stored (on the heap, 
  not on the stack).  With LIBSEH, GetExceptionCode can actually be called within a filter
  function.  However, this is not recommended, unless you don't care about compatibility with
  Microsoft C/C++.


KEEP THESE IN MIND WHEN WRITING CODE THAT WILL BE COMPILED USING MULTIPLE COMPILERS.



