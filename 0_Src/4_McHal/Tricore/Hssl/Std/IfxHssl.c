/**
 * \file IfxHssl.c
 * \brief HSSL  basic functionality
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

#include "IfxHssl.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

void IfxHssl_enableHsctModule(Ifx_HSCT *hsct)
{
    uint16 psw = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(psw); // clears the endinit protection
    hsct->CLC.B.DISR = 0;           // enables the module
    IfxScuWdt_setCpuEndinit(psw);   // sets the endinit protection back on
}


void IfxHssl_enableHsslModule(Ifx_HSSL *hssl)
{
    uint16 psw = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(psw); // clears the endinit protection
    hssl->CLC.B.DISR = 0;           // enables the module
    IfxScuWdt_setCpuEndinit(psw);   // sets the endinit protection back on
}


volatile Ifx_SRC_SRCR *IfxHssl_getHsctSrcPointer(Ifx_HSCT *hsct)
{
    return &MODULE_SRC.HSCT.HSCT[0].SR;
}


volatile Ifx_SRC_SRCR *IfxHssl_getHsslCOKSrcPointer(Ifx_HSSL *hssl, IfxHssl_ChannelId channelId)
{
    return &MODULE_SRC.HSSL.HSSL[(uint32)channelId].COK;
}


volatile Ifx_SRC_SRCR *IfxHssl_getHsslERRSrcPointer(Ifx_HSSL *hssl, IfxHssl_ChannelId channelId)
{
    return &MODULE_SRC.HSSL.HSSL[(uint32)channelId].ERR;
}


volatile Ifx_SRC_SRCR *IfxHssl_getHsslEXISrcPointer(Ifx_HSSL *hssl)
{
    return &MODULE_SRC.HSSL.EXI;
}


volatile Ifx_SRC_SRCR *IfxHssl_getHsslRDISrcPointer(Ifx_HSSL *hssl, IfxHssl_ChannelId channelId)
{
    return &MODULE_SRC.HSSL.HSSL[(uint32)channelId].RDI;
}


volatile Ifx_SRC_SRCR *IfxHssl_getHsslTRGSrcPointer(Ifx_HSSL *hssl, IfxHssl_ChannelId channelId)
{
    return &MODULE_SRC.HSSL.HSSL[(uint32)channelId].TRG;
}


void IfxHssl_resetHsctKernel(Ifx_HSCT *hsct)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();

    IfxScuWdt_clearCpuEndinit(passwd);
    hsct->KRST0.B.RST = 1;          /* Only if both Kernel reset bits are set a reset is executed */
    hsct->KRST1.B.RST = 1;
    IfxScuWdt_setCpuEndinit(passwd);

    while (0 == hsct->KRST0.B.RSTSTAT)  /* Wait until reset is executed */

    {}

    IfxScuWdt_clearCpuEndinit(passwd);
    hsct->KRSTCLR.B.CLR = 1;            /* Clear Kernel reset status bit */
    IfxScuWdt_setCpuEndinit(passwd);
}


void IfxHssl_resetHsslKernel(Ifx_HSSL *hssl)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();

    IfxScuWdt_clearCpuEndinit(passwd);
    hssl->KRST0.B.RST = 1;          /* Only if both Kernel reset bits are set a reset is executed */
    hssl->KRST1.B.RST = 1;
    IfxScuWdt_setCpuEndinit(passwd);

    while (0 == hssl->KRST0.B.RSTSTAT)  /* Wait until reset is executed */

    {}

    IfxScuWdt_clearCpuEndinit(passwd);
    hssl->KRSTCLR.B.CLR = 1;            /* Clear Kernel reset status bit */
    IfxScuWdt_setCpuEndinit(passwd);
}
