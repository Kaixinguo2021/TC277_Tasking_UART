/**
 * \file IfxFce_Crc.c
 * \brief FCE CRC details
 *
 * \version iLLD_1_0_0_11_0
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxFce_Crc.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

uint16 IfxFce_Crc_calculateCrc16(IfxFce_Crc_Crc *fce, const uint16 *crcData, uint32 crcDataLength, uint16 crcStartValue)
{
    Ifx_FCE *fceSFR = fce->fce;
    uint32   inputDataCounter;
    uint16   crcResultValue;
    uint16  *dataPtr = (uint16 *)crcData;

    fceSFR->IN2.CHECK.U  = 0xFACECAFE;
    fceSFR->IN2.LENGTH.U = 0xFACECAFE;
    fceSFR->IN2.CHECK.U  = (uint16)fce->expectedCrc;
    fceSFR->IN2.LENGTH.U = crcDataLength;

    /*Configure CRC register*/
    fceSFR->IN2.CRC.U = crcStartValue;
    {
        /*Code for CRC-16 calculaion with 0x1021 polynomial*/
        for (inputDataCounter = 0; inputDataCounter < crcDataLength; inputDataCounter++)
        {
            fceSFR->IN2.IR.U = *(dataPtr++);
        }
    }

    crcResultValue = (uint16)fceSFR->IN2.RES.U;

    return crcResultValue;
}


uint32 IfxFce_Crc_calculateCrc32(IfxFce_Crc_Crc *fce, const uint32 *crcData, uint32 crcDataLength, uint32 crcStartValue)
{
    Ifx_FCE         *fceSFR = fce->fce;
    uint32           inputDataCounter;
    uint32           crcResultValue;
    uint32          *dataPtr = (uint32 *)crcData;
    volatile uint32 *inPtr;

    /*Crc-32 calculaion with 0x04C11DB7 polynomial*/
    if (fce->crc32Kernel == IfxFce_Crc32Kernel_0)
    {
        fceSFR->IN0.CHECK.U  = 0xFACECAFE;
        fceSFR->IN0.LENGTH.U = 0xFACECAFE;
        fceSFR->IN0.CHECK.U  = fce->expectedCrc;
        fceSFR->IN0.LENGTH.U = crcDataLength;
        fceSFR->IN0.CRC.U    = crcStartValue;

        inPtr                = (volatile uint32 *)&fceSFR->IN0.IR.U;
    }
    else
    {
        fceSFR->IN1.CHECK.U  = 0xFACECAFE;
        fceSFR->IN1.LENGTH.U = 0xFACECAFE;
        fceSFR->IN1.CHECK.U  = fce->expectedCrc;
        fceSFR->IN1.LENGTH.U = crcDataLength;
        fceSFR->IN1.CRC.U    = crcStartValue;

        inPtr                = (volatile uint32 *)&fceSFR->IN1.IR.U;
    }

    {
        for (inputDataCounter = 0; inputDataCounter < crcDataLength; inputDataCounter++)
        {
            *inPtr = *(dataPtr++);
        }
    }

    if (fce->crc32Kernel == IfxFce_Crc32Kernel_0)
    {
        crcResultValue = fceSFR->IN0.RES.U;
    }
    else
    {
        crcResultValue = fceSFR->IN1.RES.U;
    }

    return crcResultValue;
}


uint8 IfxFce_Crc_calculateCrc8(IfxFce_Crc_Crc *fce, const uint8 *crcData, uint32 crcDataLength, uint8 crcStartValue)
{
    Ifx_FCE *fceSFR = fce->fce;
    uint32   inputDataCounter;
    uint8    crcResultValue;
    uint8   *dataPtr = (uint8 *)crcData;

    fceSFR->IN3.CHECK.U  = 0xFACECAFE;
    fceSFR->IN3.LENGTH.U = 0xFACECAFE;
    fceSFR->IN3.CHECK.U  = (uint8)fce->expectedCrc;
    fceSFR->IN3.LENGTH.U = crcDataLength;

    /*Configure CRC register*/
    fceSFR->IN3.CRC.U = crcStartValue;

    /*Code for CRC-8 calculaion for 0x1D polynomials*/
    {
        /* input in INIT register */
        for (inputDataCounter = 0; inputDataCounter < crcDataLength; ++inputDataCounter)
        {
            fceSFR->IN3.IR.U = *(dataPtr++);
        }
    }
    crcResultValue = (uint8)fceSFR->IN3.RES.U;

    return crcResultValue;
}


void IfxFce_Crc_clearErrorFlags(IfxFce_Crc_Crc *fce)
{
    if (fce->crcMode == IfxFce_CrcMode_8)
    {
        IfxFce_clearCrc8ErrorFlags(fce->fce);
    }
    else if (fce->crcMode == IfxFce_CrcMode_16)
    {
        IfxFce_clearCrc16ErrorFlags(fce->fce);
    }
    else
    {
        IfxFce_clearCrc32ErrorFlags(fce->fce, fce->crc32Kernel);
    }
}


void IfxFce_Crc_deInitModule(IfxFce_Crc_Crc *fce)
{
    IfxFce_resetModule(fce->fce);
}


Ifx_FCE_STS IfxFce_Crc_getInterruptStatus(IfxFce_Crc_Crc *fce)
{
    if (fce->crcMode == IfxFce_CrcMode_8)
    {
        return IfxFce_getCrc8InterruptStatus(fce->fce);
    }
    else if (fce->crcMode == IfxFce_CrcMode_16)
    {
        return IfxFce_getCrc16InterruptStatus(fce->fce);
    }
    else
    {
        return IfxFce_getCrc32InterruptStatus(fce->fce, fce->crc32Kernel);
    }
}


void IfxFce_Crc_initCrc(IfxFce_Crc_Crc *fceCrc, const IfxFce_Crc_CrcConfig *crcConfig)
{
    fceCrc->fce         = crcConfig->fce;
    Ifx_FCE    *fceSFR = crcConfig->fce;
    fceCrc->crcMode     = crcConfig->crcMode;
    fceCrc->expectedCrc = crcConfig->expectedCrc;

    uint16      password = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(password);

    Ifx_FCE_CFG tempCFG;
    tempCFG.U        = 0;
    tempCFG.B.CMI    = crcConfig->enabledInterrupts.crcMismatch;
    tempCFG.B.CEI    = crcConfig->enabledInterrupts.configError;
    tempCFG.B.LEI    = crcConfig->enabledInterrupts.lengthError;
    tempCFG.B.BEI    = crcConfig->enabledInterrupts.busError;
    tempCFG.B.CCE    = crcConfig->crcCheckCompared;
    tempCFG.B.ALR    = crcConfig->automaticLengthReload;
    tempCFG.B.REFIN  = crcConfig->dataByteReflectionEnabled;
    tempCFG.B.REFOUT = crcConfig->crc32BitReflectionEnabled;
    tempCFG.B.XSEL   = crcConfig->crcResultInverted;

    if (crcConfig->crcMode == IfxFce_CrcMode_8)
    {
        fceSFR->IN3.CFG.U = tempCFG.U;
    }
    else if (crcConfig->crcMode == IfxFce_CrcMode_16)
    {
        fceSFR->IN2.CFG.U = tempCFG.U;
    }
    else
    {
        fceCrc->crc32Kernel = crcConfig->crc32Kernel;

        if (crcConfig->crc32Kernel == IfxFce_Crc32Kernel_0)
        {
            fceSFR->IN0.CFG.U = tempCFG.U;
        }
        else
        {
            fceSFR->IN1.CFG.U = tempCFG.U;
        }
    }

    IfxScuWdt_setCpuEndinit(password);
}


void IfxFce_Crc_initCrcConfig(IfxFce_Crc_CrcConfig *crcConfig, IfxFce_Crc *fce)
{
    crcConfig->fce                           = fce->fce;
    crcConfig->crcMode                       = IfxFce_CrcMode_32;
    crcConfig->crcCheckCompared              = TRUE;
    crcConfig->automaticLengthReload         = FALSE;
    crcConfig->dataByteReflectionEnabled     = TRUE;
    crcConfig->crc32BitReflectionEnabled     = TRUE;
    crcConfig->crcResultInverted             = TRUE;
    crcConfig->enabledInterrupts.crcMismatch = FALSE; // enable if CRC is already known
    crcConfig->enabledInterrupts.configError = TRUE;
    crcConfig->enabledInterrupts.lengthError = TRUE;
    crcConfig->enabledInterrupts.busError    = TRUE;
}


void IfxFce_Crc_initModule(IfxFce_Crc *fce, const IfxFce_Crc_Config *config)
{
    fce->fce = config->fce;
    Ifx_FCE *fceSFR   = config->fce;

    uint16   password = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(password);
    IfxFce_enableModule(fceSFR);
    IfxScuWdt_setCpuEndinit(password);

    volatile Ifx_SRC_SRCR *src = IfxFce_getSrcPointer(fceSFR);
    IfxSrc_init(src, config->isrTypeOfService, config->isrPriority);
    IfxSrc_enable(src);
}


void IfxFce_Crc_initModuleConfig(IfxFce_Crc_Config *config, Ifx_FCE *fce)
{
    config->fce              = fce;
    config->isrPriority      = 0;
    config->isrTypeOfService = IfxSrc_Tos_cpu0;
}
