/** @file
  This module verifies that Enhanced Key Usages (EKU's) are present within
  a PKCS7 signature blob using OpenSSL.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.

  Copyright (C) Microsoft Corporation. All Rights Reserved.
  Copyright (c) 2019, Intel Corporation. All rights reserved.<BR>

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  1. Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

**/

#include "InternalCryptLib.h"

/**
  This function receives a PKCS#7 formatted signature blob,
  looks for the EKU SEQUENCE blob, and if found then looks
  for all the required EKUs.  This function was created so that
  the Surface team can cut down on the number of Certificate
  Authorities (CA's) by checking EKU's on leaf signers for
  a specific product.  This prevents one product's certificate
  from signing another product's firmware or unlock blobs.

  Return RETURN_UNSUPPORTED to indicate this interface is not supported.

  @param[in]  Pkcs7Signature        The PKCS#7 signed information content block. An array
                                    containing the content block with both the signature,
                                    the signer's certificate, and any necessary intermediate
                                    certificates.
  @param[in]  Pkcs7SignatureSize    Number of bytes in pPkcs7Signature.
  @param[in]  RequiredEKUs          Array of null-terminated strings listing OIDs of
                                    required EKUs that must be present in the signature.
                                    All specified EKU's must be present in order to
                                    succeed.
  @param[in]  RequiredEKUsSize      Number of elements in the rgRequiredEKUs string.
                                    This parameter has a maximum of MAX_EKU_SEARCH.
  @param[in]  RequireAllPresent     If this is TRUE, then all of the specified EKU's
                                    must be present in the leaf signer.  If it is
                                    FALSE, then we will succeed if we find any
                                    of the specified EKU's.

  @retval RETURN_UNSUPPORTED        The operation is not supported.

**/
EFI_STATUS
EFIAPI
VerifyEKUsInPkcs7Signature (
  IN CONST UINT8    *Pkcs7Signature,
  IN CONST UINT32   SignatureSize,
  IN CONST CHAR8    *RequiredEKUs[],
  IN CONST UINT32   RequiredEKUsSize,
  IN BOOLEAN        RequireAllPresent
  )
{
  ASSERT (FALSE);
  return RETURN_UNSUPPORTED;
}

