
/*******************************************************************************
 *                                                                             *
 * sehpp.cpp - C++ SEH implementation.                                         *
 *                                                                             *
 * LIBSEH - Structured Exception Handling compatibility library.               *
 * Copyright (c) 2008 Tom Bramer < tjb at postpro dot net >                    *
 *                                                                             *
 * Permission is hereby granted, free of charge, to any person                 *
 * obtaining a copy of this software and associated documentation              *
 * files (the "Software"), to deal in the Software without                     *
 * restriction, including without limitation the rights to use,                *
 * copy, modify, merge, publish, distribute, sublicense, and/or sell           *
 * copies of the Software, and to permit persons to whom the                   *
 * Software is furnished to do so, subject to the following                    *
 * conditions:                                                                 *
 *                                                                             *
 * The above copyright notice and this permission notice shall be              *
 * included in all copies or substantial portions of the Software.             *
 *                                                                             *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,             *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES             *
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                    *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT                 *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,                *
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING                *
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR               *
 * OTHER DEALINGS IN THE SOFTWARE.                                             *
 *                                                                             *
 *******************************************************************************/

/** @file sehpp.cpp
 *  Implementation of LibSEH C++ bindings.
 */

#include "../seh.h"

namespace seh
{

  int 
  __seh_exception_handler(PEXCEPTION_RECORD pRecord,
                          __seh_buf* pReg,
                          PCONTEXT pContext,
                          PEXCEPTION_RECORD pRecord2)
  {
    TRACE_START();

    switch(pRecord->ExceptionCode)
    {
      case EXCEPTION_ACCESS_VIOLATION:
        TRACE0("Throwing access violation exception");
        throw access_violation(pRecord->ExceptionAddress, NULL);
    }

    TRACE0("Throwing other exception");
    throw exception(pRecord->ExceptionCode, pRecord->ExceptionAddress);

    TRACE_END();
    return EXCEPTION_CONTINUE_SEARCH;
  }

  void 
  __initialize(__seh_buf* buf)
  {
    TRACE_START();
    memset(buf, 0, sizeof(*buf));
    buf->prev = __seh_get_registration();
    buf->handler = __seh_exception_handler;
    buf->magic = SEH_MAGIC_NUMBER;
    __seh_set_registration(buf);
    TRACE_END();
  }


  exception::exception(uint32_t code, void* address)
  {
    const int buffer_len = 80;
    char buffer[buffer_len];
    snprintf(buffer, buffer_len, "System exception code 0x%08x occurred at address 0x%08x.", code, address);
    set_msg(buffer);
  }

  const char*
  exception::what()
  {
    return msg_.c_str();
  }

  void
  exception::set_msg(const std::string& msg)
  {
    msg_ = msg;
  }

  access_violation::access_violation(void* address, void* accessaddr) : exception()
  {
    const int buffer_len = 80;
    char buffer[buffer_len];
    snprintf(buffer, buffer_len, "Access violation occurred at address 0x%08x while accessing address 0x%08x.", address, accessaddr);
    set_msg(buffer);
  }

}


