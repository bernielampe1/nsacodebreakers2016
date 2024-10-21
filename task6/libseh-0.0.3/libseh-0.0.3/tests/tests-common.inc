// Common to tests

#include <seh.h>
#include "tests.h"

DWORD exc_filter(DWORD code, DWORD filtercode)
{
    if(code == filtercode)
        return EXCEPTION_EXECUTE_HANDLER;
    return EXCEPTION_CONTINUE_SEARCH;
}

