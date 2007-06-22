/** @file
  Entry point to the PEI Core

Copyright (c) 2006, Intel Corporation<BR>
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __MODULE_ENTRY_POINT_H__
#define __MODULE_ENTRY_POINT_H__

/**

  Enrty point to PEI core.

  @param SecCoreData    Points to a data structure containing
                        information about the PEI core's
                        operating environment, such as the size
                        and location of temporary RAM, the stack
                        location and the BFV location. The type
                        EFI_SEC_PEI_HAND_OFF is

  @param PpiList        Points to a list of one or more PPI
                        descriptors to be installed initially by
                        the PEI core. An empty PPI list consists
                        of a single descriptor with the end-tag
                        EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST.
                        As part of its initialization phase, the
                        PEI Foundation will add these SEC-hosted
                        PPIs to its PPI database such that both
                        the PEI Foundation and any modules can
                        leverage the associated service calls
                        and/or code in these early PPIs.

**/
VOID
EFIAPI 
_ModuleEntryPoint(
  IN CONST  EFI_SEC_PEI_HAND_OFF    *SecCoreData,
  IN CONST  EFI_PEI_PPI_DESCRIPTOR  *PpiList
);

/**
  Wrapper of enrty point to PEI core.

  @param  PeiStartupDescriptor Pointer of start up information.
 
  @return Status returned by entry points of core and drivers. 

**/
VOID
EFIAPI
EfiMain (
  IN CONST  EFI_SEC_PEI_HAND_OFF    *SecCoreData,
  IN CONST  EFI_PEI_PPI_DESCRIPTOR  *PpiList
  );

/**
  Call constructs for all libraries. Automatics Generated by tool.

  @param  FfsHeader   Pointer to header of FFS.
  @param  PeiServices Pointer to the PEI Services Table.

**/
VOID
EFIAPI
ProcessLibraryConstructorList (
  IN EFI_FFS_FILE_HEADER  *FfsHeader,
  IN EFI_PEI_SERVICES     **PeiServices
  );


/**
  Call the list of driver entry points. Automatics Generated by tool.

  @param  PeiStartupDescriptor  Pointer to startup information .
  @param  OldCoreData           Pointer to Original startup information.

  @return Status returned by entry points of drivers.  
 
**/
VOID
EFIAPI
ProcessModuleEntryPointList (
  IN CONST  EFI_SEC_PEI_HAND_OFF    *SecCoreData,
  IN CONST  EFI_PEI_PPI_DESCRIPTOR  *PpiList,
  IN VOID                           *OldCoreData
  );

#endif
