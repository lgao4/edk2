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

**/

#include "InternalCryptLib.h"
#include <openssl/objects.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <Library/MemoryAllocationLib.h>

/**
  Encrypts a blob using PKCS1v2 (RSAES-OAEP) schema. On success, will return the encrypted message in
  in a newly allocated buffer.

  Things that can cause a failure include:
  - X509 key size does not match any known key size.
  - Fail to parse X509 certificate.
  - Fail to allocate an intermediate buffer.
  - NULL pointer provided for a non-optional parameter.
  - Data size is too large for the provided key size (max size is a function of key size and hash digest size).

  @param[in]  PublicKey     A pointer to the DER-encoded X509 certificate that will be used to encrypt the data.
  @param[in]  PublicKeySize Size of the X509 cert buffer.
  @param[in]  InData        Data to be encrypted.
  @param[in]  InDataSize    Size of the data buffer.
  @param[in]  PrngSeed      [Optional] If provided, a pointer to a random seed buffer to be used when initializing the PRNG. NULL otherwise.
  @param[in]  PrngSeedSize  [Optional] If provided, size of the random seed buffer. 0 otherwise.
  @param[out] EncryptedData       Pointer to an allocated buffer containing the encrypted message.
  @param[out] EncryptedDataSize   Size of the encrypted message buffer.

  @retval     TRUE  Encryption was successful.
  @retval     FALSE Encryption failed.

**/
BOOLEAN
Pkcs1v2Encrypt (
  IN   CONST UINT8  *PublicKey,
  IN   UINTN        PublicKeySize,
  IN   UINT8        *InData,
  IN   UINTN        InDataSize,
  IN   CONST UINT8  *PrngSeed OPTIONAL,
  IN   UINTN        PrngSeedSize OPTIONAL,
  OUT  UINT8        **EncryptedData,
  OUT  UINTN        *EncryptedDataSize
  )
{
  BOOLEAN       Result;
  CONST UINT8   *TempPointer;
  X509          *CertData;
  EVP_PKEY      *InternalPublicKey;
  EVP_PKEY_CTX  *PkeyCtx;
  UINT8         *OutData;
  UINTN         OutDataSize;

  //
  // First step, check all buffers. We *hate* NULL buffers. They burns us.
  //
  if (PublicKey == NULL || InData == NULL || EncryptedData == NULL || EncryptedDataSize == NULL)
  {
    DEBUG(( DEBUG_ERROR, "[%a:%d] - Invalid parameter!\n", __FUNCTION__, __LINE__ ));
    return FALSE;
  }

  //
  // Check public key size.
  //
  if (PublicKeySize > 0xFFFFFFFF)
  {
    DEBUG((DEBUG_ERROR, "[%a:%d] - Invalid parameter. Public Key Size too large for implementation!\n", __FUNCTION__, __LINE__));
    return FALSE;
  }

  *EncryptedData       = NULL;
  *EncryptedDataSize  = 0;
  Result               = FALSE;
  TempPointer          = NULL;
  CertData             = NULL;
  InternalPublicKey   = NULL;
  PkeyCtx              = NULL;
  OutData              = NULL;
  OutDataSize         = 0;

  //
  // Ideally, we will have been provided with a seed from a good source.
  // Otherwise, we'll seed with fixed values and hope that the PRNG has already been
  // used enough to generate sufficient entropy.
  //
  if (PrngSeed != NULL)
  {
    RandomSeed( PrngSeed, PrngSeedSize );
  }
  else
  {
    RandomSeed( NULL, 0 );
  }

  //
  // Next, we need to parse the X509 cert and extract the public key.
  //
  TempPointer = PublicKey;
  CertData = d2i_X509( &CertData, &TempPointer, (UINT32)PublicKeySize );
  if (CertData == NULL)
  {
    DEBUG(( DEBUG_ERROR, "[%a:%d] - Failed to parse x509 cert!\n", __FUNCTION__, __LINE__ ));
    goto _Exit;
  }

  //
  // Next, we must extract the public key from the x509 cert in a format that
  // OpenSSL can use.
  InternalPublicKey = X509_get_pubkey( CertData );
  if (InternalPublicKey == NULL)
  {
    DEBUG(( DEBUG_ERROR, "[%a:%d] - Failed to extract public key!\n", __FUNCTION__, __LINE__ ));
    goto _Exit;
  }

  //
  // Almost there, we need to create a context for the public key operation.
  //
  PkeyCtx = EVP_PKEY_CTX_new( InternalPublicKey, NULL );
  if (PkeyCtx == NULL)
  {
    DEBUG(( DEBUG_ERROR, "[%a:%d] - Context creation failed!\n", __FUNCTION__, __LINE__ ));
    goto _Exit;
  }
  //
  // Initialize the context and set the desired padding.
  //
  if (EVP_PKEY_encrypt_init( PkeyCtx ) <= 0 ||
      EVP_PKEY_CTX_set_rsa_padding( PkeyCtx, RSA_PKCS1_OAEP_PADDING ) <= 0)
  {
    DEBUG(( DEBUG_ERROR, "[%a:%d] - Failed to initialize the context!\n", __FUNCTION__, __LINE__ ));
    goto _Exit;
  }

  //
  // Attempt to determine the required buffer length for malloc'ing.
  //
  if (EVP_PKEY_encrypt( PkeyCtx, NULL, &OutDataSize, InData, InDataSize ) <= 0)
  {
    DEBUG(( DEBUG_ERROR, "[%a:%d]- Failed to determine output buffer size!\n", __FUNCTION__, __LINE__ ));
    goto _Exit;
  }

  //
  // We now have the size and can allocate a buffer for the output data.
  //
  OutData = AllocatePool( OutDataSize );
  if (OutData == NULL)
  {
    DEBUG(( DEBUG_ERROR, "[%a:%d] - Failed to allocate the output buffer!\n", __FUNCTION__, __LINE__ ));
    goto _Exit;
  }

  //
  // Try to encrypt something!
  //
  if (EVP_PKEY_encrypt( PkeyCtx, OutData, &OutDataSize, InData, InDataSize ) <= 0)
  {
    DEBUG(( DEBUG_ERROR, "[%a:%d] - Failed to encrypt!\n", __FUNCTION__, __LINE__ ));
    //
    // If we've had an error here, it's imperitive that we free the output buffer
    // since no one else will really get the chance.
    //
    FreePool( OutData );
    OutData = NULL;
    OutDataSize = 0;
    goto _Exit;
  }

  //
  // If we've made it this far, we best have encrypted some actual data.
  //
  *EncryptedData = OutData;
  *EncryptedDataSize = OutDataSize;
  Result = TRUE;

_Exit:
  //
  // Free anything that may have been allocated during the operation.
  //
  if (CertData != NULL)
  {
    X509_free( CertData );
  }
  if (InternalPublicKey != NULL)
  {
    EVP_PKEY_free( InternalPublicKey );
  }
  if (PkeyCtx != NULL)
  {
    EVP_PKEY_CTX_free( PkeyCtx );
  }

  return Result;
}
