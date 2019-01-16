/** @file
  This application used to test bug 1371
  BZ: https://bugzilla.tianocore.org/show_bug.cgi?id=1371

  Copyright (c) 2006 - 2019, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
// #pragma optimize( "", off )  // Decomment it if we need debug in VS2015
#include <Library/DebugLib.h>
#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Guid/GlobalVariable.h>
#include <Library/MemoryAllocationLib.h>
#include <stdarg.h>

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  UINTN                   Length; 
  UINT8                   *Buffer;

  Length = 32;

  Buffer  = AllocatePool (0x20);

  Buffer[0] = 9;
  Buffer[1] = 1;
  Buffer[11] = 73;
  Buffer[12] = 110;
  Buffer[13] = 116;
  Buffer[14] = 101;
  Buffer[15] = 108;

  DUMP_HEX (DEBUG_INFO, 0,  Buffer , Length,  "%s  ", L"Intel" );

  return EFI_SUCCESS;
}


