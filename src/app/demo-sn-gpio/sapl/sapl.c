/**
********************************************************************************
\file   sapl.c

\brief  Safe application managing module

This module manages the application near firmware parts.

\ingroup module_sapl
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

/*----------------------------------------------------------------------------*/
/* includes                                                                   */
/*----------------------------------------------------------------------------*/

#include <sapl/sapl.h>

#include <shnf/shnf.h>

#include <sapl/parameterset.h>
#include <sapl/parametercrc.h>
#include <sapl/sodstore.h>

#include <SODapi.h>
#include <SERRapi.h>
#include <SNMTSapi.h>

#include <oschecksum/crc.h>

/*============================================================================*/
/*            G L O B A L   D E F I N I T I O N S                             */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/* const defines                                                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* module global vars                                                         */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* global function prototypes                                                 */
/*----------------------------------------------------------------------------*/


/*============================================================================*/
/*            P R I V A T E   D E F I N I T I O N S                           */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/* const defines                                                              */
/*----------------------------------------------------------------------------*/
#define NVS_SOD_IMAGE_OFFSET        0x200000UL       /**< Offset of the stored SOD in the NVS */

#define SAPL_TASK_PROCESS_PARAM_SET_PARSE_BIT         0x00
#define SAPL_TASK_PROCESS_PARAM_SET_PARSE_MASK        0x01

#define SAPL_TASK_PROCESS_PARAM_SET_CRC_BIT           0x01
#define SAPL_TASK_PROCESS_PARAM_SET_CRC_MASK          0x02

#define SAPL_TASK_PROCESS_PARAM_SET_STORE_BIT         0x02
#define SAPL_TASK_PROCESS_PARAM_SET_STORE_MASK        0x04


/*----------------------------------------------------------------------------*/
/* local types                                                                */
/*----------------------------------------------------------------------------*/

/**
 * \brief Details of the incomming parameter set
 */
typedef struct
{
    void * pData_m;         /**< Pointer to the start of the parameter set */
    UINT32 length_m;        /**< Actual length of the parameter set */
} tParamSetAttr;

/**
 * \brief SAPL instance structure
 */
typedef struct
{
    UINT32 activeTasks_m;             /**< Stores which task of the SAPL is currently active */
    BOOLEAN * pEnterOperational_m;    /**< Pointer to the switch to operational flag */
    BOOLEAN fParamCrcValid_m;         /**< TRUE if the parameter CRC is valid */
    tParamSetAttr paramSetAttr_m;     /**< Attributes of the SOD parameter set */
} tSaplInstance;

/*----------------------------------------------------------------------------*/
/* local vars                                                                 */
/*----------------------------------------------------------------------------*/
static tSaplInstance saplInstance_l SAFE_INIT_SEKTOR;

/*----------------------------------------------------------------------------*/
/* local function prototypes                                                  */
/*----------------------------------------------------------------------------*/

/*============================================================================*/
/*            P U B L I C   F U N C T I O N S                                 */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/**
\brief    Initialize safe application main modules

\param pEnterOperational_p      Pointer to the operational flag

\retval TRUE    Initialization was successful
\retval FALSE   Error during initialization

\ingroup module_sapl
*/
/*----------------------------------------------------------------------------*/
BOOLEAN sapl_init(BOOLEAN * pEnterOperational_p)
{
    BOOLEAN fReturn = FALSE;

    MEMSET(&saplInstance_l, 0, sizeof(tSaplInstance));

    if(pEnterOperational_p != NULL)
    {
        saplInstance_l.pEnterOperational_m = pEnterOperational_p;

        /* Initialize the parameter set module */
        if(paramset_init())
        {
            /* Initialize the SOD CRC calculation module */
            if(paramcrc_init())
            {
                /* Initialize the SOD storage module */
                if(sodstore_init(NVS_SOD_IMAGE_OFFSET))
                {
                    fReturn = TRUE;
                }
            }
        }
    }
    else
    {
        errh_postFatalError(kErrSourceSapl, kErrorInvalidParameter, 0);
    }

    return fReturn;
}

/*----------------------------------------------------------------------------*/
/**
\brief    Shutdown the SAPL module

\ingroup module_sapl
*/
/*----------------------------------------------------------------------------*/
void sapl_exit(void)
{
    paramset_exit();
    paramcrc_exit();

    sodstore_close();
}

/*----------------------------------------------------------------------------*/
/**
\brief    Process the SAPL background task

\retval TRUE    Processing of the SAPL successful
\retval FALSE   Error during processing

\ingroup module_sapl
*/
/*----------------------------------------------------------------------------*/
BOOLEAN sapl_process(void)
{
    BOOLEAN fReturn = FALSE;
    tProcParamRet paramProcRet;
    tProcCrcRet paramCrcRet;
    tProcStoreRet sodStoreRet;

    if((saplInstance_l.activeTasks_m & SAPL_TASK_PROCESS_PARAM_SET_PARSE_MASK) != 0)
    {
        /* Process the parameter parser state machine */
        paramProcRet = paramset_process((UINT8*)saplInstance_l.paramSetAttr_m.pData_m,
                                        saplInstance_l.paramSetAttr_m.length_m);
        if(paramProcRet == kParamProcFinished)
        {
            /* Reset the flag of the parameter parser */
            saplInstance_l.activeTasks_m &= ~(1<<SAPL_TASK_PROCESS_PARAM_SET_PARSE_BIT);
            /* Store the currently processed parameter set to the NVS */
            saplInstance_l.activeTasks_m |= (1<<SAPL_TASK_PROCESS_PARAM_SET_STORE_BIT);

            fReturn = TRUE;
        }
        else if(paramProcRet == kParamProcBusy)
        {
            /* Continue processing on next call of SAPL process */
            fReturn = TRUE;
        }
    }
    else if((saplInstance_l.activeTasks_m & SAPL_TASK_PROCESS_PARAM_SET_CRC_MASK) != 0)
    {
        /* Process calculation of the SOD checksum */
        paramCrcRet = paramcrc_process();
        if(paramCrcRet == kParamCrcProcCrcValid)
        {
            /* Tell stack if the received checksum matches the calculated checksum */
            SNMTS_PassParamChkSumValid(B_INSTNUM_ TRUE);
            fReturn = TRUE;
            saplInstance_l.fParamCrcValid_m = TRUE;

            /* Reset the flag of the CRC calculator */
            saplInstance_l.activeTasks_m &= ~(1<<SAPL_TASK_PROCESS_PARAM_SET_CRC_BIT);
        }
        else if(paramCrcRet == kParamCrcProcCrcInvalid)
        {
            /* Report invalid checksum to stack */
            SNMTS_PassParamChkSumValid(B_INSTNUM_ FALSE);
            fReturn = TRUE;

            /* Reset the flag of the CRC calculator */
            saplInstance_l.activeTasks_m &= ~(1<<SAPL_TASK_PROCESS_PARAM_SET_CRC_BIT);
        }
        else if(paramCrcRet == kParamCrcProcBusy)
        {
            /* Continue processing on next call of SAPL process */
            fReturn = TRUE;
        }
    }
    else if((saplInstance_l.activeTasks_m & SAPL_TASK_PROCESS_PARAM_SET_STORE_MASK) != 0)
    {
        /* Process the SOD store state machine */
        sodStoreRet = sodstore_process((UINT8*)saplInstance_l.paramSetAttr_m.pData_m,
                                       saplInstance_l.paramSetAttr_m.length_m);
        if(sodStoreRet == kSodStoreProcFinished)
        {
            /* Reset the flag of the parameter store task */
            saplInstance_l.activeTasks_m &= ~(1<<SAPL_TASK_PROCESS_PARAM_SET_STORE_BIT);

            fReturn = TRUE;
        }
        else if(sodStoreRet == kSodStoreProcBusy)
        {
            /* Continue processing on next call of SAPL process */
            fReturn = TRUE;
        }
    }
    else
    {
        /* Nothing to process -> Success! */
        fReturn = TRUE;
    }

    return fReturn;
}

/*----------------------------------------------------------------------------*/
/**
\brief    Check if there is an SOD image in the NVS and restore it if so

\retval TRUE    Restore successful or nothing to restore
\retval FALSE   Error during restore of the image

\ingroup module_sapl
*/
/*----------------------------------------------------------------------------*/
BOOLEAN sapl_restoreSod(void)
{
    BOOLEAN fReturn = FALSE;
    UINT8* pParamSetBase = NULL;
    UINT32 paramSetLen = 0;
    tProcParamRet procRet;

    if(sodstore_getSodImage(&pParamSetBase, &paramSetLen))
    {
        /* A valid SOD image is in the NVS -> Restore it with the parameter parser */
        do
        {
            procRet = paramset_process(pParamSetBase, paramSetLen);

        } while(procRet != kParamProcFinished || procRet == kParamProcError);

        if(procRet == kParamProcFinished)
        {
            fReturn = TRUE;
        }
    }
    else
    {
        /* No image available -> Continue normal bootup */
        fReturn = TRUE;
    }

    return fReturn;
}

/**
 *
 * The function is called by the openSAFETY Stack (unit SNMTS) to indicate that a SN state transition from
 * PRE-OPERATIONAL to OPERATIONAL was requested by the SCM. To be able to respond the requested state
 * transition the openSAFETY Application has to admit the transition  by calling the function SNMTS_EnterOpState().
 *
 * @attention To inform the SNMTS about the API confirmation of switching into state OPERATIONAL application
 * must call the API function SNMTS_EnterOpState(). This API function MUST NOT be called within this callback function.
 *
 * @param        b_instNum        instance number, valid range: 0 .. &lt;EPLS_cfg_MAX_INSTANCES&gt; - 1
 *
 */
void SAPL_SNMTS_SwitchToOpReqClbk(BYTE_B_INSTNUM)
{
#if (EPLS_cfg_MAX_INSTANCES > 1)
    b_instNum = b_instNum; /* To avoid warnings */
#endif

    /*
     * Verify if the parameter checksum is indeed valid
     * and all SAPL tasks are finished!
     */
    if(saplInstance_l.fParamCrcValid_m == TRUE  &&
       saplInstance_l.activeTasks_m == 0         )
    {
        saplInstance_l.fParamCrcValid_m = FALSE;
        *saplInstance_l.pEnterOperational_m = TRUE;
    }
}

/**
 *
 * The function is called by the openSAFETY Stack (unit SNMTS) in case of reception of SNMT Service "SN set to OPERATIONAL".
 * This callback function requests the application of the SN to calculate the checksum of the current SOD.
 *
 * @attention To pass the calculated parameter checksum to the SNMTS the application must call the API function
 * SNMTS_PassParamChkSumValid(). This API function MUST NOT be called within this callback function.
 *
 * @param       b_instNum         instance number, valid range:  0 .. &lt;EPLS_cfg_MAX_INSTANCES&gt; - 1
 *
 */
void SAPL_SNMTS_CalcParamChkSumClbk(BYTE_B_INSTNUM)
{
#if (EPLS_cfg_MAX_INSTANCES > 1)
    b_instNum = b_instNum; /* To avoid warnings */
#endif

    /* Start the CRC calculation in the background */
    paramcrc_startProcessing();

    /* Enable corresponding task in SAPL process */
    saplInstance_l.activeTasks_m |= (1<<SAPL_TASK_PROCESS_PARAM_SET_CRC_BIT);
}

/**
 * @brief This function is a callback function which is provided by the openSAFETY Application. The function is called by the
 * openSAFETY Stack (unit SNMTS) to check whether the "parameter set" downloaded by the SCM is already processed.
 *
 * @param        b_instNum        instance number, valid range: 0 .. &lt;EPLS_cfg_MAX_INSTANCES&gt; - 1
 *
 * @return
 * - TRUE           - "parameter set" is already processed
 * - FALSE          - "parameter set" is not processed
 */
BOOLEAN SAPL_SNMTS_ParameterSetProcessed(BYTE_B_INSTNUM)
{
    BOOLEAN procFin = FALSE;

#if (EPLS_cfg_MAX_INSTANCES > 1)
    UNUSED_PARAMETER(b_instNum);    /* to avoid warnings */
#endif

    if((saplInstance_l.activeTasks_m & SAPL_TASK_PROCESS_PARAM_SET_PARSE_MASK) == 0)
    {
        /* Indicate processing finished */
        procFin = TRUE;
    }

    return procFin;
}


/*
 * This function is called after the write access of the parameter
 * set object.Parameter set object has SOD index 0x101A
 * sub-index 0x00.
 *
 * \param B_INSTNUM    instance number
 * \param e_srvc       type of service, see {SOD_t_SERVICE}
 *                     (not checked, only called with enum
 *                     value in CallBeforeReadClbk() or
 *                     CallBeforeWriteClbk() or
 *                     CallAfterWriteClbk())
 *                     valid range: SOD_t_SERVICE
 * \param ps_obj       pointer to a SOD entry, see
 *                     {SOD_t_OBJECT} (pointer not checked,
 *                     only called with reference to struct
 *                     in SOD_Read() or SOD_Write())
 *                     valid range: pointer to a SOD_t_OBJECT
 * \param pv_data      pointer to data to be written, in case
 *                     of SOD_k_SRV_BEFORE_WRITE, otherwise
 *                     NULL (pointer not checked)
 *                     valid range: pointer to data to be
 *                     written, in case of
 *                     SOD_k_SRV_BEFORE_WRITE, otherwise NULL
 * \param dw_offset    start offset in bytes of the segment
 *                     within the data block (not used)
 * \param dw_size      size in bytes of the segment (not used)
 * \param pe_abortCode abort code has to be set for the SSDO if
 *                     the return value is FALSE.
 *                     (pointer not checked, only called with
 *                     reference to variable)
 *                     valid range: pointer to the
 *                     SOD_t_ABORT_CODES
 *
 * \return - TRUE  - success
 *         - FALSE - failure
 */
BOOLEAN SAPL_SOD_ParameterSet_CLBK(BYTE_B_INSTNUM_ SOD_t_SERVICE e_srvc,
                                   const SOD_t_OBJECT *ps_obj,
                                   const void *pv_data,
                                   UINT32 dw_offset, UINT32 dw_size,
                                   SOD_t_ABORT_CODES *pe_abortCode)
{
    BOOLEAN fReturn = FALSE;

    /* The parameter set is handled in the process function in the background.
     * Therefore these function parameters are not used!
     */
    UNUSED_PARAMETER(e_srvc);
    UNUSED_PARAMETER(ps_obj);
    UNUSED_PARAMETER(dw_offset);
    UNUSED_PARAMETER(pv_data);
    UNUSED_PARAMETER(dw_size);

    /* Check used parameters sanity */
    if( ps_obj == NULL              ||
        ps_obj->pv_objData == NULL  ||
        pe_abortCode == NULL         )
    {
        errh_postFatalError(kErrSourceSapl, kErrorInvalidParameter, 0);

        if(pe_abortCode != NULL)
        {
            *pe_abortCode = SOD_ABT_GENERAL_ERROR;
        }
    }
    else
    {
        /* Store parameter set attributes */
        saplInstance_l.paramSetAttr_m.pData_m = ((SOD_t_ACT_LEN_PTR_DATA*)(ps_obj->pv_objData))->pv_objData;
        saplInstance_l.paramSetAttr_m.length_m = ((SOD_t_ACT_LEN_PTR_DATA*)(ps_obj->pv_objData))->dw_actLen;

        saplInstance_l.activeTasks_m |= (1<<SAPL_TASK_PROCESS_PARAM_SET_PARSE_BIT);

        *pe_abortCode   = SOD_ABT_NO_ERROR;

        fReturn = TRUE;
    }

    return fReturn;
}

/**
 * HNFiff_Crc32CalcSwp
 * calculates the checksymbols of a buffer (\a buf) of length \a len bytes,
 * using a table (\a crctab) which contains the checksymbols for the values 0
 * up to 255. It is possible to calculate the crc of a huge buffer in several
 * chuncks. For this reason the parameter \a initcrc is used.\n
 * To init a chunckwise calculation \a buf is set to the beginning of the
 * buffer, \a len holds the chuncksize, and \a initcrc is set zero.
 * To continue a chunckwise calculation the buffer pointer \a (buf) must be
 * updated and \a initcrc is loaded with the result of the previous function
 * call.\n
 * If \a initcrc is nonzero when the first call of a calculation (entire
 * buffer or partial) is done, the result is a coset code.
 * \retval  crc value
 */
UINT32 HNFiff_Crc32CalcSwp(UINT32 w_initCrc, INT32 l_length,
                           const void *pv_data)
{
    return crc32Checksum(l_length, (UINT8*)pv_data, w_initCrc);
}

/*============================================================================*/
/*            P R I V A T E   F U N C T I O N S                               */
/*============================================================================*/
/* \name Private Functions */
/* \{ */

/* \} */

