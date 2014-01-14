/**
********************************************************************************
\file   icc.c

\brief  Configuration channel input module

Input module of the configuration channel module. Reads objects from the
triple buffers.

\ingroup module_icc
*******************************************************************************/

/*------------------------------------------------------------------------------
* License Agreement
*
* Copyright 2013 BERNECKER + RAINER, AUSTRIA, 5142 EGGELSBERG, B&R STRASSE 1
* All rights reserved.
*
* Redistribution and use in source and binary forms,
* with or without modification,
* are permitted provided that the following conditions are met:
*
*   * Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer
*     in the documentation and/or other materials provided with the
*     distribution.
*   * Neither the name of the B&R nor the names of its contributors
*     may be used to endorse or promote products derived from this software
*     without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------*/

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include <appif/icc.h>

#include <appifcommon/ccobject.h>
#include <appif/status.h>
#include <appif/tbuf.h>

#include <Epl.h>

//============================================================================//
//            G L O B A L   D E F I N I T I O N S                             //
//============================================================================//

//------------------------------------------------------------------------------
// const defines
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// module global vars
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// global function prototypes
//------------------------------------------------------------------------------


//============================================================================//
//            P R I V A T E   D E F I N I T I O N S                           //
//============================================================================//

//------------------------------------------------------------------------------
// const defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// local types
//------------------------------------------------------------------------------


/**
\brief Configuration channel input instance type

The configuration channel input instance holds information about the
input triple buffer.
*/
typedef struct
{
    tTbufInstance        pTbufInstance_m;      ///< Instance pointer to the triple buffer
    tSeqNrValue          currSeq_m;            ///< Current sequence flag of the channel
    UINT8                fObjIncomming_m;      ///< True when a new object is in the buffer

} tConfChanInInstance;

//------------------------------------------------------------------------------
// local vars
//------------------------------------------------------------------------------

static tConfChanInInstance          iccInstance_l;

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------

static tAppIfStatus icc_grabObject(tConfChanObject*  pObject_p);

//============================================================================//
//            P U B L I C   F U N C T I O N S                                 //
//============================================================================//

//------------------------------------------------------------------------------
/**
\brief    Initialize the configuration channel input module

\param[in] pInitParam_p            Icc initialization parameters

\return  tAppIfStatus
\retval  kAppIfSuccessful              On success
\retval  kAppIfConfChanInitError       Unable to init conf chan module

\ingroup module_icc
*/
//------------------------------------------------------------------------------
tAppIfStatus icc_init(tIccInitStruct* pInitParam_p)
{
    tAppIfStatus    ret = kAppIfSuccessful;
    tTbufInitStruct tbufInitParam;

    APPIF_MEMSET(&iccInstance_l, 0 , sizeof(tConfChanInInstance));

#if _DEBUG
    if(pInitParam_p->tbufSize_m != sizeof(tTbufCcStructure))
    {
        ret = kAppIfConfChanBufferSizeMismatch;
        goto Exit;
    }
#endif

    // init the triple buffer module
    tbufInitParam.id_m = pInitParam_p->id_m;
    tbufInitParam.pAckBase_m = pInitParam_p->pConsAckBase_m;
    tbufInitParam.pBase_m = (UINT8 *)pInitParam_p->pTbufBase_m;
    tbufInitParam.size_m = pInitParam_p->tbufSize_m;

    iccInstance_l.pTbufInstance_m = tbuf_create(&tbufInitParam);
    if(iccInstance_l.pTbufInstance_m == NULL)
    {
        ret = kAppIfConfChanInitError;
        goto Exit;
    }

Exit:
    return ret;
}

//------------------------------------------------------------------------------
/**
\brief    Destroy the configuration channel input module

\ingroup module_icc
*/
//------------------------------------------------------------------------------
void icc_exit(void)
{
    // Destroy triple buffer
    tbuf_destroy(iccInstance_l.pTbufInstance_m);

}

//------------------------------------------------------------------------------
/**
\brief    Handle incoming objects

Grab the next object out of the buffer and forward it to the object list.
(This function is called in interrupt context)

\return  tAppIfStatus
\retval  kAppIfSuccessful          On success
\retval  kAppIfTbuffReadError      Error on reading
\retval  other error               Unable to forward objects to buffer

\ingroup module_icc
*/
//------------------------------------------------------------------------------
tAppIfStatus icc_handleIncoming(void)
{
    tAppIfStatus     ret = kAppIfSuccessful;
    tSeqNrValue      currSeq = kSeqNrValueInvalid;

    if(iccInstance_l.fObjIncomming_m != FALSE)
    {
        // Object access is currently in progress -> do nothing here!
        goto Exit;
    }

    // Acknowledge consuming buffer
    ret = tbuf_setAck(iccInstance_l.pTbufInstance_m);
    if(ret != kAppIfSuccessful)
    {
        goto Exit;
    }

    // Get current sequence number
    ret = tbuf_readByte(iccInstance_l.pTbufInstance_m, TBUF_SEQNR_OFF, (UINT8 *)&currSeq);
    if(ret != kAppIfSuccessful)
    {
        goto Exit;
    }

    // Check sequence number sanity
    if(currSeq != kSeqNrValueFirst && currSeq != kSeqNrValueSecond)
    {
        goto Exit;
    }

    if(currSeq != iccInstance_l.currSeq_m)
    {
        // Set object incoming flag
        iccInstance_l.fObjIncomming_m = TRUE;

        // Increment local sequence number
        iccInstance_l.currSeq_m = currSeq;
    }

Exit:
    return ret;
}

//------------------------------------------------------------------------------
/**
\brief    Process icc object access

Grab an object out of the internal FIFO and forward it to the local object
dictionary.

\return  tAppIfStatus
\retval  kAppIfSuccessful                   On success
\retval  kAppIfConfChanWriteToObDictFailed  Unable to forward object to obdict
\retval  kAppIfFifoEmpty                    No element in the FIFO

\ingroup module_icc
*/
//------------------------------------------------------------------------------
tAppIfStatus icc_process(void)
{
    tAppIfStatus     ret = kAppIfSuccessful;
    tEplKernel       eplret = kEplSuccessful;
    tConfChanObject  object;

    APPIF_MEMSET(&object, 0, sizeof(tConfChanObject));

    if(iccInstance_l.fObjIncomming_m)
    {
        // Incoming element (Update local structures)

        ret = icc_grabObject(&object);
        if(ret == kAppIfSuccessful)
        {
            // Update object in object list
            if(ccobject_writeObject(&object) == FALSE)
            {
                goto Exit;
            }

            // Write object data to local obdict.h
            eplret = oplk_writeLocalObject(object.objIdx_m, object.objSubIdx_m,
                    &object.objPayloadLow_m, object.objSize_m);
            if(eplret != kEplSuccessful)
            {
                ret = kAppIfConfChanWriteToObDictFailed;
            }
        }
        else
        {
            // TODO signal error to application
            DEBUG_TRACE(DEBUG_LVL_ERROR, "ERROR: Received invalid object from icc channel! Ret: 0x%x!\n", ret);
            ret = kAppIfSuccessful;
        }

        // Reset incoming flag
        iccInstance_l.fObjIncomming_m = FALSE;

        // Set current icc status flag
        status_setIccStatus(iccInstance_l.currSeq_m);
    }

Exit:
    return ret;
}

//============================================================================//
//            P R I V A T E   F U N C T I O N S                               //
//============================================================================//
/// \name Private Functions
/// \{

//------------------------------------------------------------------------------
/**
\brief    Grab object data out of triple buffer

\param[out] pObject_p     Pointer to the read object data

\return  tAppIfStatus
\retval  kAppIfSuccessful        On success
\retval  kAppIfTbuffReadError    Unable to read from the buffer

\ingroup module_icc
*/
//------------------------------------------------------------------------------
static tAppIfStatus icc_grabObject(tConfChanObject*  pObject_p)
{
    tAppIfStatus           ret = kAppIfSuccessful;
    UINT8                  size;

    // Get object index
    ret = tbuf_readByte(iccInstance_l.pTbufInstance_m, TBUF_OBJSUBIDX_OFF,
            &pObject_p->objSubIdx_m);
    if(ret != kAppIfSuccessful)
    {
        goto Exit;
    }

    // Get object subindex
    ret = tbuf_readWord(iccInstance_l.pTbufInstance_m, TBUF_OBJIDX_OFF,
            &pObject_p->objIdx_m);
    if(ret != kAppIfSuccessful)
    {
        goto Exit;
    }

    // Grab size from local list
    if(ccobject_getObjectSize(pObject_p->objIdx_m, pObject_p->objSubIdx_m, &size) == FALSE)
    {
        goto Exit;
    }

    // Save object size
    pObject_p->objSize_m = size;

    switch(size)
    {
        case sizeof(UINT8):
        {
            ret = tbuf_readByte(iccInstance_l.pTbufInstance_m, TBUF_PAYLOADLOW_OFF,
                    (UINT8 *)&pObject_p->objPayloadLow_m);
            break;
        }
        case sizeof(UINT16):
        {
            ret = tbuf_readWord(iccInstance_l.pTbufInstance_m, TBUF_PAYLOADLOW_OFF,
                    (UINT16 *)&pObject_p->objPayloadLow_m);
            break;
        }
        case sizeof(UINT32):
        {
            ret = tbuf_readDword(iccInstance_l.pTbufInstance_m, TBUF_PAYLOADLOW_OFF,
                    &pObject_p->objPayloadLow_m);
            break;
        }
        case sizeof(UINT64):
        {
            ret = tbuf_readDword(iccInstance_l.pTbufInstance_m, TBUF_PAYLOADLOW_OFF,
                    &pObject_p->objPayloadLow_m);
            if(ret != kAppIfSuccessful)
            {
                goto Exit;
            }

            ret = tbuf_readDword(iccInstance_l.pTbufInstance_m, TBUF_PAYLOADHIGH_OFF,
                    &pObject_p->objPayloadHigh_m);
            break;
        }
        default:
        {
            ret = kAppIfConfChanInvalidSizeOfObj;
            break;
        }
    }


Exit:
    return ret;
}

/// \}

