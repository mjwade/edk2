/** @file

  Copyright (c) 2008 - 2010, Apple Inc. All rights reserved.<BR>
  
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Base.h>

#include <Library/BaseLib.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>


UINTN
EFIAPI
MicroSecondDelay (
  IN  UINTN MicroSeconds
  )
{
  UINT64  NanoSeconds;
  
  NanoSeconds = MultU64x32 (MicroSeconds, 1000);

  while (NanoSeconds > (UINTN)-1) { 
    NanoSecondDelay((UINTN)-1);
    NanoSeconds -= (UINTN)-1;
  }

  NanoSecondDelay (NanoSeconds);

  return MicroSeconds;
}

UINTN
EFIAPI
NanoSecondDelay (
  IN  UINTN NanoSeconds
  )
{
  UINT32  Delay;
  UINT32  StartTime;
  UINT32  CurrentTime;
  UINT32  ElapsedTime;

 
  Delay = (NanoSeconds / PcdGet32(PcdEmbeddedPerformanceCounterPeriodInNanoseconds)) + 1;

  StartTime = MmioRead32 (0);
  do 
  {
    CurrentTime = 0ULL;
    ElapsedTime = CurrentTime - StartTime;
  } while (ElapsedTime < Delay);

  NanoSeconds = ElapsedTime * PcdGet32 (PcdEmbeddedPerformanceCounterPeriodInNanoseconds);

  return NanoSeconds;
}

UINT64
EFIAPI
GetPerformanceCounter (
  VOID
  )
{ 
  return (UINT64)0ULL;
}

UINT64
EFIAPI
GetPerformanceCounterProperties (
  OUT UINT64  *StartValue,  OPTIONAL
  OUT UINT64  *EndValue     OPTIONAL
  )
{
  if (StartValue != NULL) {
    // Timer starts with the reload value
    *StartValue = (UINT64)0ULL;
  }
  
  if (EndValue != NULL) {
    // Timer counts up to 0xFFFFFFFF
    *EndValue = 0xFFFFFFFF;
  }
  
  return PcdGet64(PcdEmbeddedPerformanceCounterFrequencyInHz);
}