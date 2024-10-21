
#include "tests-common.inc"

BEGIN_SIMPLE_TEST(null_pointer)
{
  int* x = 0;

  __try {
    volatile int y = *x;
    TEST_FAILED("The access violation exception was not raised as expected");
  }
  __except(exc_filter(GetExceptionCode(), EXCEPTION_ACCESS_VIOLATION))
  {
    TEST_PASSED(); 
  }
  __end_except

  TEST_FAILED("The exception was not caught by the exception handler.");
}
END_TEST()
