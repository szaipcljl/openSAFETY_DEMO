/**
********************************************************************************
\file   demo_safety/objdict/objdict.h

\brief  Object dictionary according to CiA401

This file contains the object dictionary definition for the CANopen CiA401
device profile.
*******************************************************************************/

/*------------------------------------------------------------------------------
Copyright (c) 2013, Bernecker+Rainer Industrie-Elektronik Ges.m.b.H. (B&R)
Copyright (c) 2013, SYSTEC electronic GmbH
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holders nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------*/

#include <appif/obdict.h>

#define OBD_DEFINE_MACRO
    #include "obdmacro.h"
#undef OBD_DEFINE_MACRO

OBD_BEGIN ()

    OBD_BEGIN_PART_GENERIC ()

        #include "../generic/objdict_1000-13ff.h"

        // Object 1400h: PDO_RxCommParam_00h_REC
        OBD_BEGIN_INDEX_RAM(0x1400, 0x03, pdou_cbObdAccess)
            OBD_SUBINDEX_RAM_VAR(0x1400, 0x00, kObdTypeUInt8, kObdAccConst, tObdUnsigned8, NumberOfEntries, 0x02)
            OBD_SUBINDEX_RAM_VAR(0x1400, 0x01, kObdTypeUInt8, kObdAccRW, tObdUnsigned8, NodeID_U8, 0x00)
            OBD_SUBINDEX_RAM_VAR(0x1400, 0x02, kObdTypeUInt8, kObdAccRW, tObdUnsigned8, MappingVersion_U8, 0x00)
        OBD_END_INDEX(0x1400)

        // Object 1401h: PDO_RxCommParam_01h_REC
        OBD_BEGIN_INDEX_RAM(0x1401, 0x03, pdou_cbObdAccess)
            OBD_SUBINDEX_RAM_VAR(0x1401, 0x00, kObdTypeUInt8, kObdAccConst, tObdUnsigned8, NumberOfEntries, 0x02)
            OBD_SUBINDEX_RAM_VAR(0x1401, 0x01, kObdTypeUInt8, kObdAccRW, tObdUnsigned8, NodeID_U8, 0x00)
            OBD_SUBINDEX_RAM_VAR(0x1401, 0x02, kObdTypeUInt8, kObdAccRW, tObdUnsigned8, MappingVersion_U8, 0x00)
        OBD_END_INDEX(0x1401)

        // Object 1402h: PDO_RxCommParam_02h_REC
        OBD_BEGIN_INDEX_RAM(0x1402, 0x03, pdou_cbObdAccess)
            OBD_SUBINDEX_RAM_VAR(0x1402, 0x00, kObdTypeUInt8, kObdAccConst, tObdUnsigned8, NumberOfEntries, 0x02)
            OBD_SUBINDEX_RAM_VAR(0x1402, 0x01, kObdTypeUInt8, kObdAccRW, tObdUnsigned8, NodeID_U8, 0x00)
            OBD_SUBINDEX_RAM_VAR(0x1402, 0x02, kObdTypeUInt8, kObdAccRW, tObdUnsigned8, MappingVersion_U8, 0x00)
        OBD_END_INDEX(0x1402)

        // Object 1600h: PDO_RxMappParam_00h_AU64
        OBD_BEGIN_INDEX_RAM(0x1600, 0x1A, pdou_cbObdAccess)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x00, kObdTypeUInt8, kObdAccRW, tObdUnsigned8, NumberOfEntries, 0x00)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x01, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x02, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x03, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x04, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x05, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x06, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x07, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x08, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x09, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x0A, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x0B, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x0C, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x0D, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x0E, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x0F, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x10, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x11, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x12, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x13, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x14, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x15, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x16, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x17, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x18, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1600, 0x19, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
        OBD_END_INDEX(0x1600)

        // Object 1601h: PDO_RxMappParam_01h_AU64
        OBD_BEGIN_INDEX_RAM(0x1601, 0x1A, pdou_cbObdAccess)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x00, kObdTypeUInt8, kObdAccRW, tObdUnsigned8, NumberOfEntries, 0x00)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x01, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x02, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x03, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x04, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x05, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x06, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x07, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x08, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x09, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x0A, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x0B, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x0C, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x0D, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x0E, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x0F, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x10, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x11, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x12, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x13, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x14, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x15, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x16, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x17, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x18, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1601, 0x19, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
        OBD_END_INDEX(0x1601)

		// Object 1602h: PDO_RxMappParam_02h_AU64
        OBD_BEGIN_INDEX_RAM(0x1602, 0x1A, pdou_cbObdAccess)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x00, kObdTypeUInt8, kObdAccRW, tObdUnsigned8, NumberOfEntries, 0x00)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x01, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x02, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x03, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x04, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x05, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x06, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x07, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x08, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x09, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x0A, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x0B, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x0C, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x0D, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x0E, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x0F, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x10, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x11, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x12, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x13, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x14, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x15, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x16, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x17, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x18, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1602, 0x19, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
        OBD_END_INDEX(0x1602)

        // Object 1800h: PDO_TxCommParam_00h_REC
        OBD_BEGIN_INDEX_RAM(0x1800, 0x03, pdou_cbObdAccess)
            OBD_SUBINDEX_RAM_VAR(0x1800, 0x00, kObdTypeUInt8, kObdAccConst, tObdUnsigned8, NumberOfEntries, 0x02)
            OBD_SUBINDEX_RAM_VAR(0x1800, 0x01, kObdTypeUInt8, kObdAccRW, tObdUnsigned8, NodeID_U8, 0x00)
            OBD_SUBINDEX_RAM_VAR(0x1800, 0x02, kObdTypeUInt8, kObdAccRW, tObdUnsigned8, MappingVersion_U8, 0x00)
        OBD_END_INDEX(0x1800)

        // Object 1A00h: PDO_TxMappParam_00h_AU64
        OBD_BEGIN_INDEX_RAM(0x1A00, 0x1A, pdou_cbObdAccess)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x00, kObdTypeUInt8, kObdAccRW, tObdUnsigned8, NumberOfEntries, 0x0)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x01, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x02, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x03, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x04, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x05, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x06, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x07, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x08, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x09, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x0A, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x0B, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x0C, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x0D, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x0E, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x0F, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x10, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x11, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x12, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x13, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x14, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x15, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x16, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x17, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x18, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
            OBD_SUBINDEX_RAM_VAR(0x1A00, 0x19, kObdTypeUInt64, kObdAccRW, tObdUnsigned64, ObjectMapping, 0x00LL)
        OBD_END_INDEX(0x1A00)

        #include "../generic/objdict_1b00-1fff.h"

    OBD_END_PART ()

    OBD_BEGIN_PART_MANUFACTURER ()

#if(((APPIF_MODULE_INTEGRATION) & (APPIF_MODULE_CC)) != 0)
    // add manufacturer part objects (2000h .. 5fffh) here
        OBD_BEGIN_INDEX_RAM(0x2000, 0x05, cc_obdAccessCb)
            OBD_SUBINDEX_RAM_VAR(0x2000, 0x00, kObdTypeUInt8, kObdAccConst, tObdUnsigned8, NumberOfEntries, 0x04)
            OBD_SUBINDEX_RAM_VAR(0x2000, 0x01, kObdTypeUInt16, kObdAccRW, tObdUnsigned16, UserParameter_01, 0x00)
            OBD_SUBINDEX_RAM_VAR(0x2000, 0x02, kObdTypeUInt16, kObdAccRW, tObdUnsigned16, UserParameter_02, 0x00)
            OBD_SUBINDEX_RAM_VAR(0x2000, 0x03, kObdTypeUInt16, kObdAccRW, tObdUnsigned16, UserParameter_03, 0x00)
            OBD_SUBINDEX_RAM_VAR(0x2000, 0x04, kObdTypeUInt16, kObdAccRW, tObdUnsigned16, UserParameter_04, 0x00)
        OBD_END_INDEX(0x2000)
#endif

#if(((APPIF_MODULE_INTEGRATION) & (APPIF_MODULE_ASYNC)) != 0)
        // SSDO-Stub
        OBD_BEGIN_INDEX_RAM(0x3000, 0x03, NULL)
            OBD_SUBINDEX_RAM_VAR(0x3000, 0x00, kObdTypeUInt8, kObdAccConst, tObdUnsigned8, NumberOfEntries, 0x02)
            OBD_SUBINDEX_RAM_VAR(0x3000, 0x01, kObdTypeUInt32, kObdAccRW, tObdUnsigned32, SSDOStubAddress_U32, 0x00)
            OBD_SUBINDEX_RAM_VAR(0x3000, 0x02, kObdTypeUInt32, kObdAccRW, tObdUnsigned32, SSDOStubAddress_U32, 0x00)
        OBD_END_INDEX(0x3000)

        // SSDO-StubData
        OBD_BEGIN_INDEX_RAM(0x3100, 0x03, appif_asyncObdAccessCb)
            OBD_SUBINDEX_RAM_VAR(0x3100, 0x00, kObdTypeUInt8, kObdAccConst, tObdUnsigned8, NumberOfEntries, 0x02)
            OBD_SUBINDEX_RAM_OSTRING(0x3100, 0x01, kObdAccRW, SSDOStubData_DOM, 0x20)
            OBD_SUBINDEX_RAM_OSTRING(0x3100, 0x02, kObdAccRW, SSDOStubData_DOM, 0x20)
        OBD_END_INDEX(0x3100)
#endif

    OBD_END_PART ()

    OBD_BEGIN_PART_DEVICE ()

        OBD_BEGIN_INDEX_RAM(0x6000, 0x01, NULL)
            OBD_SUBINDEX_RAM_DOMAIN(0x6000, 0x00, kObdAccVPR, STPDO_0)
        OBD_END_INDEX(0x6000)

        OBD_BEGIN_INDEX_RAM(0x6200, 0x01, NULL)
            OBD_SUBINDEX_RAM_DOMAIN(0x6200, 0x00, kObdAccVPRW, SRPDO_0)
        OBD_END_INDEX(0x6200)

    OBD_END_PART ()

OBD_END ()


#define OBD_UNDEFINE_MACRO
    #include "obdmacro.h"
#undef OBD_UNDEFINE_MACRO

