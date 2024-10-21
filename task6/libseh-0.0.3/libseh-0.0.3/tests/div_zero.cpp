
#include "tests-common.inc"

BEGIN_SIMPLE_TEST(divzero)
{
  int x = 0;

  __try {
    volatile int y = 4 / x;
    TEST_FAILED("The exception was not caught by the exception handler.");
  }
  __except(exc_filter(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO))
  {
    TEST_PASSED(); 
  }
  __end_except

}
END_TEST()
