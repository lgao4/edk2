/** @file
  This file contains UEFI wrapper functions for RSA PKCS1v2 OAEP encryption routines.

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

  Copyright (C) 2016 Microsoft Corporation. All Rights Reserved.
  Copyright (c) 2019, Intel Corporation. All rights reserved.<BR>

**/

#include "InternalCryptLib.h"

/**
  Encrypts a blob using PKCS1v2 (RSAES-OAEP) schema. On success, will return the
  encrypted message in a newly allocated buffer.

  Return FALSE to indicate this interface is not supported.

  @param[in]  PublicKey           A pointer to the DER-encoded X509 certificate that
                                  will be used to encrypt the data.
  @param[in]  PublicKeySize       Size of the X509 cert buffer.
  @param[in]  InData              Data to be encrypted.
  @param[in]  InDataSize          Size of the data buffer.
  @param[in]  PrngSeed            [Optional] If provided, a pointer to a random seed buffer
                                  to be used when initializing the PRNG. NULL otherwise.
  @param[in]  PrngSeedSize        [Optional] If provided, size of the random seed buffer.
                                  0 otherwise.
  @param[out] EncryptedData       Pointer to an allocated buffer containing the encrypted
                                  message.
  @param[out] EncryptedDataSize   Size of the encrypted message buffer.

  @retval FALSE                   This interface is not supported.

**/
BOOLEAN
EFIAPI
Pkcs1v2Encrypt (
  IN   CONST UINT8  *PublicKey,
  IN   UINTN        PublicKeySize,
  IN   UINT8        *InData,
  IN   UINTN        InDataSize,
  IN   CONST UINT8  *PrngSeed,  OPTIONAL
  IN   UINTN        PrngSeedSize,  OPTIONAL
  OUT  UINT8        **EncryptedData,
  OUT  UINTN        *EncryptedDataSize
  )
{
  ASSERT (FALSE);
  return FALSE;
}

