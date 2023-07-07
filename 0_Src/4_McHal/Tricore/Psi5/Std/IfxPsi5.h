/**
 * \file IfxPsi5.h
 * \brief PSI5  basic functionality
 * \ingroup IfxLld_Psi5
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
 * \defgroup IfxLld_Psi5_Std_Enumerations Enumerations
 * \ingroup IfxLld_Psi5_Std
 * \defgroup IfxLld_Psi5_Std_Channel Channel Status Functions
 * \ingroup IfxLld_Psi5_Std
 * \defgroup IfxLld_Psi5_Std_IO IO Pin Configuration Functions
 * \ingroup IfxLld_Psi5_Std
 * \defgroup IfxLld_Psi5_Std_Interrupt Interrupt configuration function
 * \ingroup IfxLld_Psi5_Std
 */

#ifndef IFXPSI5_H
#define IFXPSI5_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_Impl/IfxPsi5_cfg.h"
#include "_PinMap/IfxPsi5_PinMap.h"
#include "IfxPsi5_reg.h"
#include "Scu/Std/IfxScuWdt.h"
#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "Src/Std/IfxSrc.h"

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Psi5_Std_Enumerations
 * \{ */
/** \brief MODULE_PSI5.IOCRx.ALTI(x = 0,1,2),Alternate input selection
 */
typedef enum
{
    IfxPsi5_AlternateInput_0 = 0,      /**< \brief Alternate Input  0  */
    IfxPsi5_AlternateInput_1,          /**< \brief Alternate Input  1  */
    IfxPsi5_AlternateInput_2,          /**< \brief Alternate Input  2  */
    IfxPsi5_AlternateInput_3           /**< \brief Alternate Input  3  */
} IfxPsi5_AlternateInput;

/** \brief MODULE_PSI5.RCRCx.BRS(x = 0,1,2),Baud rate selection
 */
typedef enum
{
    IfxPsi5_BaudRate_125 = 0,  /**< \brief Slow 125 kHz clock */
    IfxPsi5_BaudRate_189 = 1   /**< \brief Fast 189 kHz clock */
} IfxPsi5_BaudRate;

/** \brief MODULE_PSI5.RCRBx.CRCy(x = 0,1,2; y=0,1,2,3,4,5),CRC or parity selection
 */
typedef enum
{
    IfxPsi5_CRCorParity_parity = 0,  /**< \brief parity selection */
    IfxPsi5_CRCorParity_crc    = 1   /**< \brief CRC selection */
} IfxPsi5_CRCorParity;

/** \brief Clock type
 */
typedef enum
{
    IfxPsi5_ClockType_fracDiv       = 0,  /**< \brief Fractional Divide clock */
    IfxPsi5_ClockType_slowClock_125 = 1,  /**< \brief Slow 125 kHz clock */
    IfxPsi5_ClockType_fastClock_189 = 2,  /**< \brief Fast 189 kHz clock */
    IfxPsi5_ClockType_timeStamp     = 3   /**< \brief Timestamp clock */
} IfxPsi5_ClockType;

/** \brief MODULE_PSI5.IOCRx.DEPTH(x = 0,1,2),Digital input filter depth
 */
typedef enum
{
    IfxPsi5_DigitalInputFilterDepth_0 = 0,      /**< \brief Digital input filter depth is  0  */
    IfxPsi5_DigitalInputFilterDepth_1,          /**< \brief Digital input filter depth is  1  */
    IfxPsi5_DigitalInputFilterDepth_2,          /**< \brief Digital input filter depth is  2  */
    IfxPsi5_DigitalInputFilterDepth_3,          /**< \brief Digital input filter depth is  3  */
    IfxPsi5_DigitalInputFilterDepth_4,          /**< \brief Digital input filter depth is  4  */
    IfxPsi5_DigitalInputFilterDepth_5,          /**< \brief Digital input filter depth is  5  */
    IfxPsi5_DigitalInputFilterDepth_6,          /**< \brief Digital input filter depth is  6  */
    IfxPsi5_DigitalInputFilterDepth_7,          /**< \brief Digital input filter depth is  7  */
    IfxPsi5_DigitalInputFilterDepth_8,          /**< \brief Digital input filter depth is  8  */
    IfxPsi5_DigitalInputFilterDepth_9,          /**< \brief Digital input filter depth is  9  */
    IfxPsi5_DigitalInputFilterDepth_10,         /**< \brief Digital input filter depth is  10  */
    IfxPsi5_DigitalInputFilterDepth_11,         /**< \brief Digital input filter depth is  11  */
    IfxPsi5_DigitalInputFilterDepth_12,         /**< \brief Digital input filter depth is  12  */
    IfxPsi5_DigitalInputFilterDepth_13,         /**< \brief Digital input filter depth is  13  */
    IfxPsi5_DigitalInputFilterDepth_14,         /**< \brief Digital input filter depth is  14  */
    IfxPsi5_DigitalInputFilterDepth_15          /**< \brief Digital input filter depth is  15  */
} IfxPsi5_DigitalInputFilterDepth;

/** \brief MODULE_PSI5.FDR.DM,Divider mode
 */
typedef enum
{
    IfxPsi5_DividerMode_spb        = 0,  /**< \brief divider mode is off */
    IfxPsi5_DividerMode_normal     = 1,  /**< \brief divider mode is normal */
    IfxPsi5_DividerMode_fractional = 2,  /**< \brief divider mode is fractional */
    IfxPsi5_DividerMode_off        = 3   /**< \brief divider mode is off */
} IfxPsi5_DividerMode;

/** \brief MODULE_PSI5.RCRBx.FECy(x = 0,1,2; y=0,1,2,3,4,5),Frame expectation control
 */
typedef enum
{
    IfxPsi5_FrameExpectation_notExpected = 0,  /**< \brief No frame is expected */
    IfxPsi5_FrameExpectation_expected    = 1   /**< \brief Frame is expected */
} IfxPsi5_FrameExpectation;

/** \brief MODULE_PSI5.RCRBx.MSGy(x = 0,1,2; y=0,1,2,3,4,5),Messaging bits presence
 */
typedef enum
{
    IfxPsi5_MessagingBits_absent  = 0, /**< \brief No messaging bits */
    IfxPsi5_MessagingBits_present = 1  /**< \brief 2 messaging bits */
} IfxPsi5_MessagingBits;

/** \brief MODULE_PSI5.RCRCx.TSR(x = 0,1,2),Timestamp select for receive data registers
 */
typedef enum
{
    IfxPsi5_ReceiveDataRegisterTimestamp_pulse = 0,  /**< \brief Pulse based timestamp SPTSC to be stored in RDRHC */
    IfxPsi5_ReceiveDataRegisterTimestamp_frame = 1   /**< \brief Start of frame based timestamp SPTSC to be stored in RDRHC */
} IfxPsi5_ReceiveDataRegisterTimestamp;

/** \brief MODULE_PSI5.RDRHx.SC(x = 0-2),Slot Id
 */
typedef enum
{
    IfxPsi5_Slot_0 = 0,      /**< \brief slot 0  */
    IfxPsi5_Slot_1,          /**< \brief slot 1  */
    IfxPsi5_Slot_2,          /**< \brief slot 2  */
    IfxPsi5_Slot_3,          /**< \brief slot 3  */
    IfxPsi5_Slot_4,          /**< \brief slot 4  */
    IfxPsi5_Slot_5           /**< \brief slot 5  */
} IfxPsi5_Slot;

/** \brief MODULE_PSI5.PGCx.TBS(x = 0,1,2),Time base
 */
typedef enum
{
    IfxPsi5_TimeBase_internal = 0,  /**< \brief Internal time stamp clock */
    IfxPsi5_TimeBase_external = 1   /**< \brief External GTM inputs */
} IfxPsi5_TimeBase;

/** \brief MODULE_PSI5.RCRCx.TSP(x = 0,1,2),MODULE_PSI5.RCRCx.TSF(x = 0,1,2)Timestamp register type
 */
typedef enum
{
    IfxPsi5_TimestampRegister_a = 0,  /**< \brief Timestamp register A */
    IfxPsi5_TimestampRegister_b = 1,  /**< \brief Timestamp register B */
    IfxPsi5_TimestampRegister_c = 2   /**< \brief Timestamp register C */
} IfxPsi5_TimestampRegister;

/** \brief MODULE_PSI5.PGCx.ETS(x = 0,1,2),Trigger Id
 */
typedef enum
{
    IfxPsi5_Trigger_0 = 0,      /**< \brief trigger  0  */
    IfxPsi5_Trigger_1,          /**< \brief trigger  1  */
    IfxPsi5_Trigger_2,          /**< \brief trigger  2  */
    IfxPsi5_Trigger_3,          /**< \brief trigger  3  */
    IfxPsi5_Trigger_4,          /**< \brief trigger  4  */
    IfxPsi5_Trigger_5           /**< \brief trigger  5  */
} IfxPsi5_Trigger;

/** \brief Trigger type
 */
typedef enum
{
    IfxPsi5_TriggerType_periodic = 0,  /**< \brief Periodic trigger */
    IfxPsi5_TriggerType_external = 1,  /**< \brief External trigger */
    IfxPsi5_TriggerType_bypass   = 2   /**< \brief Bypassed trigger */
} IfxPsi5_TriggerType;

/** \brief MODULE_PSI5.RCRBx.VBSy(x = 0,1,2; y=0,1,2,3,4,5),Verbose mode
 */
typedef enum
{
    IfxPsi5_Verbose_off = 0,  /**< \brief Verbose mode is turned off */
    IfxPsi5_Verbose_on  = 1   /**< \brief Verbose mode is turned on */
} IfxPsi5_Verbose;

/** \} */

/** \addtogroup IfxLld_Psi5_Std_Channel
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief access function to get the CRCI status register contents for a channel
 * \param psi5 pointer to the PSI5 register space
 * \param channel channel Id
 * \return Crci status register contents
 */
IFX_INLINE uint32 IfxPsi5_getStatusCrci(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel);

/** \brief access function to get the MEI status register contents for a channel
 * \param psi5 pointer to the PSI5 register space
 * \param channel channel Id
 * \return Mei status register contents
 */
IFX_INLINE uint32 IfxPsi5_getStatusMei(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel);

/** \brief access function to get the NBI status register contents for a channel
 * \param psi5 pointer to the PSI5 register space
 * \param channel channel Id
 * \return Nbi status register contents
 */
IFX_INLINE uint32 IfxPsi5_getStatusNbi(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel);

/** \brief access function to get the NFI status register contents for a channel
 * \param psi5 pointer to the PSI5 register space
 * \param channel channel Id
 * \return Nfi status register contents
 */
IFX_INLINE uint32 IfxPsi5_getStatusNfi(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel);

/** \brief access function to get the RDI status register contents for a channel
 * \param psi5 pointer to the PSI5 register space
 * \param channel channel Id
 * \return Rdi status register contents
 */
IFX_INLINE uint32 IfxPsi5_getStatusRdi(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel);

/** \brief access function to get the RMI status register contents for a channel
 * \param psi5 pointer to the PSI5 register space
 * \param channel channel Id
 * \return Rmi status register contents
 */
IFX_INLINE uint32 IfxPsi5_getStatusRmi(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel);

/** \brief access function to get the RSI status register contents for a channel
 * \param psi5 pointer to the PSI5 register space
 * \param channel channel Id
 * \return Rsi status register contents
 */
IFX_INLINE uint32 IfxPsi5_getStatusRsi(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel);

/** \brief access function to get the TEI status register contents for a channel
 * \param psi5 pointer to the PSI5 register space
 * \param channel channel Id
 * \return Tei status register contents
 */
IFX_INLINE uint32 IfxPsi5_getStatusTei(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief resets PSI5 kernel
 * \param psi5 pointer to PSI5 registers
 * \return None
 */
IFX_EXTERN void IfxPsi5_resetModule(Ifx_PSI5 *psi5);

/** \} */

/** \addtogroup IfxLld_Psi5_Std_IO
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Initializes a RX input
 * \param rx the RX Pin which should be configured
 * \param inputMode pin input mode which should be configured
 * \return None
 */
IFX_INLINE void IfxPsi5_initRxPin(const IfxPsi5_Rx_In *rx, IfxPort_InputMode inputMode);

/** \brief Initializes a TX output
 * \param tx the TX Pin which should be configured
 * \param outputMode the pin output mode which should be configured
 * \param padDriver the pad driver mode which should be configured
 * \return None
 */
IFX_INLINE void IfxPsi5_initTxPin(const IfxPsi5_Tx_Out *tx, IfxPort_OutputMode outputMode, IfxPort_PadDriver padDriver);

/** \brief Sets the alternate RX input
 * \param psi5Ch pointer to the PSI5 channel register space
 * \param alternateInput Alternate RX input selection
 * \return None
 */
IFX_INLINE void IfxPsi5_setRxInput(Ifx_PSI5_CH *psi5Ch, IfxPsi5_AlternateInput alternateInput);

/** \} */

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE uint32 IfxPsi5_getStatusCrci(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel)
{
    return psi5->CRCIOV[channel].U;
}


IFX_INLINE uint32 IfxPsi5_getStatusMei(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel)
{
    return psi5->MEIOV[channel].U;
}


IFX_INLINE uint32 IfxPsi5_getStatusNbi(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel)
{
    return psi5->NBIOV[channel].U;
}


IFX_INLINE uint32 IfxPsi5_getStatusNfi(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel)
{
    return psi5->NFIOV[channel].U;
}


IFX_INLINE uint32 IfxPsi5_getStatusRdi(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel)
{
    return psi5->RDIOV[channel].U;
}


IFX_INLINE uint32 IfxPsi5_getStatusRmi(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel)
{
    return psi5->RMIOV[channel].U;
}


IFX_INLINE uint32 IfxPsi5_getStatusRsi(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel)
{
    return psi5->RSIOV[channel].U;
}


IFX_INLINE uint32 IfxPsi5_getStatusTei(Ifx_PSI5 *psi5, IfxPsi5_ChannelId channel)
{
    return psi5->TEIOV[channel].U;
}


IFX_INLINE void IfxPsi5_initRxPin(const IfxPsi5_Rx_In *rx, IfxPort_InputMode inputMode)
{
    IfxPort_setPinModeInput(rx->pin.port, rx->pin.pinIndex, inputMode);
    Ifx_PSI5    *psi5   = rx->module;
    Ifx_PSI5_CH *psi5Ch = &psi5->CH[rx->channelId];
    IfxPsi5_setRxInput(psi5Ch, (IfxPsi5_AlternateInput)rx->select);
}


IFX_INLINE void IfxPsi5_initTxPin(const IfxPsi5_Tx_Out *tx, IfxPort_OutputMode outputMode, IfxPort_PadDriver padDriver)
{
    IfxPort_setPinModeOutput(tx->pin.port, tx->pin.pinIndex, outputMode, tx->select);
    IfxPort_setPinPadDriver(tx->pin.port, tx->pin.pinIndex, padDriver);
}


IFX_INLINE void IfxPsi5_setRxInput(Ifx_PSI5_CH *psi5Ch, IfxPsi5_AlternateInput alternateInput)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(passwd);
    psi5Ch->IOCR.B.ALTI = alternateInput;
    IfxScuWdt_setCpuEndinit(passwd);
}


#endif /* IFXPSI5_H */
