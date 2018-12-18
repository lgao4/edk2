/** @file
  Provides hack function for passng GCC build.

  Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "BaseLibInternals.h"

/**
  Hack function for passing GCC build. This is for X64.
**/
VOID
__chkstk()
{
}

/*
  Hack function for passing CLANGWIN build. This is for IA32.
  https://metricpanda.com/rival-fortress-update-45-dealing-with-__chkstk-__chkstk_ms-when-cross-compiling-for-windows

  LLVM and mingw don't support __chkstk disabling
  Unfortunately LLVM's code generator for Windows targets use an hard-coded probe size of 4K as of LLVM 5.0,
  and this size can only be changed on a per-function basis with the stack-probe-size function attribute.
*/
VOID
_chkstk()
{
}
