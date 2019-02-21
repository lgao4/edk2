/** @file
  Implementation of Reset2, ResetFilter and ResetHandler PPIs.

  Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <PiPei.h>
#include <Ppi/DebugPpi.h>
#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>

EDKII_DEBUG_PPI mPpiDebug = {
  DebugPrintValist,
  DebugAssert
};

EFI_PEI_PPI_DESCRIPTOR mPpiListDebug = {
  EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gEdkiiDebugPpiGuid,
  &mPpiDebug
};

/**
  The PEIM's entry point.

  @param[in] FileHandle  Handle of the file being invoked.
  @param[in] PeiServices Describes the list of possible PEI Services.

  @retval EFI_SUCCESS         The entry point is executed successfully.
  @retval EFI_ALREADY_STARTED The Reset2 PPI was already installed.
  @retval others              Status code returned from PeiServicesInstallPpi().

**/
EFI_STATUS
EFIAPI
InitializePei (
  IN EFI_PEI_FILE_HANDLE     FileHandle,
  IN CONST EFI_PEI_SERVICES  **PeiServices
  )
{
  EFI_STATUS  Status;

  Status = PeiServicesInstallPpi (&mPpiListDebug);
  ASSERT_EFI_ERROR (Status);

  return Status;
}
