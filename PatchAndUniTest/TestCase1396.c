/** @file
  This application used to test bug 1396
	BZ: https://bugzilla.tianocore.org/show_bug.cgi?id=1396
  

  Copyright (c) 2006 - 2019, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
// #pragma optimize( "", off )  // Decomment it if we need debug in VS2015
#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Guid/GlobalVariable.h>


GLOBAL_REMOVE_IF_UNREFERENCED EFI_STRING_ID mStringHelpTokenId = STRING_TOKEN (STR_HELLO_WORLD_HELP_INFORMATION);

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
  EFI_STATUS                      Status; 
  UINT64                          Data;
  UINTN                           DataSize;
  UINT32                          Attributes1;
  UINT32                          Attributes2;
  CHAR16                          *Value;
  Data = 0;
  Attributes1 = 0;
  Attributes2 = 0;

  DataSize = sizeof(UINT64);  
  
  Status = gRT->GetVariable (
                  L"Timeout",
                  &gEfiGlobalVariableGuid,
                  &Attributes1,
                  &DataSize,
                  &Data
                  );
  if (Status == EFI_SUCCESS) {
    Print (L"Attributes1 value is %d.(via GetVariable)\n", Attributes1); 
  } 
  
  Status = GetVariable3(
              L"Timeout",
             &gEfiGlobalVariableGuid,
             (VOID **)&Value,
             &DataSize, 
             &Attributes2
             );
  
  if (Status == EFI_SUCCESS) {
      Print (L"Attributes2 value is %d.(via GetVariable3)\n", Attributes2); 
  }
	
	if (Attributes2 == Attributes1){
    Print (L"Pass\n"); 
	}
	else {
		Print (L"Fail\n");  
	}

  return EFI_SUCCESS;
}
