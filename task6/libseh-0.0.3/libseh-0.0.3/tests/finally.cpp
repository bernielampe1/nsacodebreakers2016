
#include "tests-common.inc"


int finally_flag = 0;

int evil_divide_function(int n1, int n2)
{
  __try {
    return n1 / n2;

  }
  __finally {
      finally_flag = 1;
  }
  __end_finally

  TEST_FAILED("The exception was not caught by the exception handler.");
  
  return 0;
}


BEGIN_SIMPLE_TEST(finally)
{
  int x = 0;

  __try {
    int y = evil_divide_function(2, 0);
    TEST_FAILED("The divide by zero exception was not raised as expected");
  }
  __except(exc_filter(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO))
  {
      if(finally_flag == 1) {
        TEST_PASSED(); 
      }

      TEST_FAILED("Exception was caught, but finally was not called.");
  }
  __end_except

  TEST_FAILED("The exception was not caught by the exception handler.");
}
END_TEST()
