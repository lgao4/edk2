/** @file
  Debug PPI definition.

Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>

This program and the accompanying materials
are licensed and made available under the terms and conditions
of the BSD License which accompanies this distribution.  The
full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _DEBUG_PPI_H_
#define _DEBUG_PPI_H_

#define EDKII_DEBUG_PPI_GUID \
  { 0x33cbdfab, 0xbfe7, 0x4073, {0xbd, 0xb9, 0x4d, 0xc5, 0xd5, 0x48, 0x2a, 0x9b}}

/**
  Prints a debug message to the debug output device if the specified error level is enabled.

  If any bit in ErrorLevel is also set in DebugPrintErrorLevelLib function
  GetDebugPrintErrorLevel (), then print the message specified by Format and the
  associated variable argument list to the debug output device.

  If Format is NULL, then ASSERT().

  If the length of the message string specificed by Format is larger than the maximum allowable
  record length, then directly return and not print it.

  @param  ErrorLevel    The error level of the debug message.
  @param  Format        Format string for the debug message to print.
  @param  VaListMarker  VA_LIST marker for the variable argument list.

**/
typedef
VOID
(EFIAPI *EDKII_DEBUG_PRINT_VALIST) (
  IN  UINTN        ErrorLevel,
  IN  CONST CHAR8  *Format,
  IN  VA_LIST       VaListMarker
  );

/**
  Prints an assert message containing a filename, line number, and description.
  This may be followed by a breakpoint or a dead loop.

  Print a message of the form "ASSERT <FileName>(<LineNumber>): <Description>\n"
  to the debug output device.  If DEBUG_PROPERTY_ASSERT_BREAKPOINT_ENABLED bit of
  PcdDebugProperyMask is set then CpuBreakpoint() is called. Otherwise, if
  DEBUG_PROPERTY_ASSERT_DEADLOOP_ENABLED bit of PcdDebugProperyMask is set then
  CpuDeadLoop() is called.  If neither of these bits are set, then this function
  returns immediately after the message is printed to the debug output device.
  DebugAssert() must actively prevent recursion.  If DebugAssert() is called while
  processing another DebugAssert(), then DebugAssert() must return immediately.

  If FileName is NULL, then a <FileName> string of "(NULL) Filename" is printed.
  If Description is NULL, then a <Description> string of "(NULL) Description" is printed.

  @param  FileName     The pointer to the name of the source file that generated the assert condition.
  @param  LineNumber   The line number in the source file that generated the assert condition
  @param  Description  The pointer to the description of the assert condition.

**/
typedef
VOID
(EFIAPI *EDKII_DEBUG_ASSERT) (
  IN CONST CHAR8  *FileName,
  IN UINTN        LineNumber,
  IN CONST CHAR8  *Description
  );

typedef struct {
  EDKII_DEBUG_PRINT_VALIST  DebugPrintValist;
  EDKII_DEBUG_ASSERT        DebugAssert;
} EDKII_DEBUG_PPI;

extern EFI_GUID gEdkiiDebugPpiGuid;

#endif
