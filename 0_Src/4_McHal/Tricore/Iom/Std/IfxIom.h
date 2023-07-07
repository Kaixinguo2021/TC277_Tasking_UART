/**
 * \file IfxIom.h
 * \brief IOM  basic functionality
 * \ingroup IfxLld_Iom
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
 * \defgroup IfxLld_Iom_Std_Enumerations Enumerations
 * \ingroup IfxLld_Iom_Std
 * \defgroup IfxLld_Iom_Std_Module Module Functions
 * \ingroup IfxLld_Iom_Std
 */

#ifndef IFXIOM_H
#define IFXIOM_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_Impl/IfxIom_cfg.h"
#include "IfxIom_reg.h"
#include "Scu/Std/IfxScuWdt.h"
#include "Cpu/Std/IfxCpu_Intrinsics.h"

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Iom_Std_Enumerations
 * \{ */
/** \brief Specifies the edge type which need to be cleared.
 */
typedef enum
{
    IfxIom_EdgeClearType_rising        = 0, /**< \brief Specifies  rising edge  to be cleared. */
    IfxIom_EdgeClearType_falling       = 1, /**< \brief Specifies  falling edge  to be cleared. */
    IfxIom_EdgeClearType_risingFalling = 2  /**< \brief Specifies  both rising falling edge  to be cleared. */
} IfxIom_EdgeClearType;

/** \brief LAMCFG[lamId].EDS, Specifies which active edges of the monitor and reference signals are used for the event window generation.
 */
typedef enum
{
    IfxIom_EventActiveEdgeSelection_neitherGateNeitherClear   = 0,   /**< \brief neither edge used to gate event generation and neither edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_neitherGatePositiveClear  = 1,   /**< \brief neither edge used to gate event generation and positive edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_neitherGateNegativeClear  = 2,   /**< \brief neither edge used to gate event generation and negative edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_neitherGateEitherClear    = 3,   /**< \brief neither edge used to gate event generation and either edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_positiveGateNeitherClear  = 4,   /**< \brief positive edge used to gate event generation and neither edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_positiveGatePositiveClear = 5,   /**< \brief positive edge used to gate event generation and positive edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_positiveGateNegativeClear = 6,   /**< \brief positive edge used to gate event generation and negative edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_positiveGateEitherClear   = 7,   /**< \brief positive edge used to gate event generation and negative edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_negativeGateNeitherClear  = 8,   /**< \brief negative edge used to gate event generation and neither edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_negativeGatePositiveClear = 9,   /**< \brief negative edge used to gate event generation and positive edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_negativeGateNegativeClear = 10,  /**< \brief negative edge used to gate event generation and negative edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_negativeGateEitherClear   = 11,  /**< \brief negative edge used to gate event generation and either edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_eitherGateNeitherClear    = 12,  /**< \brief either edge used to gate event generation and neither edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_eitherGatePositiveClear   = 13,  /**< \brief either edge used to gate event generation and positive edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_eitherGateNegativeClear   = 14,  /**< \brief either edge used to gate event generation and negative edge used to clear event windowcounter. */
    IfxIom_EventActiveEdgeSelection_eitherGateEitherClear     = 15   /**< \brief either edge used to gate event generation and either edge used to clear event windowcounter. */
} IfxIom_EventActiveEdgeSelection;

/** \brief ECMCCFG.SELCx(x= 0,1,2,3), Specifies which channel event output is to be routed to counterCn.
 */
typedef enum
{
    IfxIom_EventCounterChannel_0 = 0,      /**< \brief channel 0 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_1,          /**< \brief channel 1 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_2,          /**< \brief channel 2 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_3,          /**< \brief channel 3 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_4,          /**< \brief channel 4 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_5,          /**< \brief channel 5 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_6,          /**< \brief channel 6 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_7,          /**< \brief channel 7 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_8,          /**< \brief channel 8 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_9,          /**< \brief channel 9 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_10,         /**< \brief channel 10 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_11,         /**< \brief channel 11 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_12,         /**< \brief channel 12 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_13,         /**< \brief channel 13 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_14,         /**< \brief channel 14 event output to be routed to event counter  */
    IfxIom_EventCounterChannel_15          /**< \brief channel 15 event output to be routed to event counter  */
} IfxIom_EventCounterChannel;

/** \brief ECMCCFG.THRCx(x= 0,1,2,3), Specifies the threshold count value. Upon the counter meeting the threshold, the counter event output becomes active high
 */
typedef enum
{
    IfxIom_EventCounterThreshold_disable = 0,  /**< \brief Specifies counter event output set to
                                                * inactive */
    IfxIom_EventCounterThreshold_1       = 1,  /**< \brief Specifies threshold count value 1  */
    IfxIom_EventCounterThreshold_2,            /**< \brief Specifies threshold count value 2  */
    IfxIom_EventCounterThreshold_3,            /**< \brief Specifies threshold count value 3  */
    IfxIom_EventCounterThreshold_4,            /**< \brief Specifies threshold count value 4  */
    IfxIom_EventCounterThreshold_5,            /**< \brief Specifies threshold count value 5  */
    IfxIom_EventCounterThreshold_6,            /**< \brief Specifies threshold count value 6  */
    IfxIom_EventCounterThreshold_7,            /**< \brief Specifies threshold count value 7  */
    IfxIom_EventCounterThreshold_8,            /**< \brief Specifies threshold count value 8  */
    IfxIom_EventCounterThreshold_9,            /**< \brief Specifies threshold count value 9  */
    IfxIom_EventCounterThreshold_10,           /**< \brief Specifies threshold count value 10  */
    IfxIom_EventCounterThreshold_11,           /**< \brief Specifies threshold count value 11  */
    IfxIom_EventCounterThreshold_12,           /**< \brief Specifies threshold count value 12  */
    IfxIom_EventCounterThreshold_13,           /**< \brief Specifies threshold count value 13  */
    IfxIom_EventCounterThreshold_14,           /**< \brief Specifies threshold count value 14  */
    IfxIom_EventCounterThreshold_15            /**< \brief Specifies threshold count value 15  */
} IfxIom_EventCounterThreshold;

/** \brief LAMCFG[lamId].EWS, Specifies whether the event window generation is from the monitor or reference signal.
 */
typedef enum
{
    IfxIom_EventSource_reference = 0,  /**< \brief Specifies  the event window generation is from the reference signal. */
    IfxIom_EventSource_monitor   = 1   /**< \brief Specifies  the event window generation is from the monitor signal. */
} IfxIom_EventSource;

/** \brief FPCCTR[channelId].MOD, Specifies the Filter & Prescaler Cell mode
 */
typedef enum
{
    IfxIom_FilterMode_delayedDebounce                               = 0,  /**< \brief Specifies Delayed Debounce filter mode */
    IfxIom_FilterMode_immediateDebounce                             = 1,  /**< \brief Specifies Immediate Debounce filter mode */
    IfxIom_FilterMode_risingEdgeImmediateDebounce                   = 2,  /**< \brief Specifies Rising Edge Immediate Debounce filter mode */
    IfxIom_FilterMode_fallingEdgeImmediateDebounce                  = 3,  /**< \brief Specifies Falling Edge Immediate Debounce filter mode */
    IfxIom_FilterMode_risingEdgeDelayedFallingEdgeImmediateDebounce = 4,  /**< \brief Specifies RisingEdge Delayed FallingEdge Immediate Debounce filter mode */
    IfxIom_FilterMode_fallingEdgeDelayedRisingEdgeImmediateDebounce = 5,  /**< \brief Specifies FallingEdge Delayed  RisingEdge Immediate Debounce filter mode */
    IfxIom_FilterMode_risingEdgePrescaler                           = 6,  /**< \brief Specifies  RisingEdge Prescaler filter mode */
    IfxIom_FilterMode_FallingEdgePrescaler                          = 7   /**< \brief Specifies  FallingEdge Prescaler filter mode */
} IfxIom_FilterMode;

/** \brief Specifies the number of Filter & Prescaler Cell channel Id
 */
typedef enum
{
    IfxIom_FpcChannelId_0 = 0,      /**< \brief Specifies the FPC channel  0  */
    IfxIom_FpcChannelId_1,          /**< \brief Specifies the FPC channel  1  */
    IfxIom_FpcChannelId_2,          /**< \brief Specifies the FPC channel  2  */
    IfxIom_FpcChannelId_3,          /**< \brief Specifies the FPC channel  3  */
    IfxIom_FpcChannelId_4,          /**< \brief Specifies the FPC channel  4  */
    IfxIom_FpcChannelId_5,          /**< \brief Specifies the FPC channel  5  */
    IfxIom_FpcChannelId_6,          /**< \brief Specifies the FPC channel  6  */
    IfxIom_FpcChannelId_7,          /**< \brief Specifies the FPC channel  7  */
    IfxIom_FpcChannelId_8,          /**< \brief Specifies the FPC channel  8  */
    IfxIom_FpcChannelId_9,          /**< \brief Specifies the FPC channel  9  */
    IfxIom_FpcChannelId_10,         /**< \brief Specifies the FPC channel  10  */
    IfxIom_FpcChannelId_11,         /**< \brief Specifies the FPC channel  11  */
    IfxIom_FpcChannelId_12,         /**< \brief Specifies the FPC channel  12  */
    IfxIom_FpcChannelId_13,         /**< \brief Specifies the FPC channel  13  */
    IfxIom_FpcChannelId_14,         /**< \brief Specifies the FPC channel  14  */
    IfxIom_FpcChannelId_15          /**< \brief Specifies the FPC channel  15  */
} IfxIom_FpcChannelId;

/** \brief LAMCFG[lamId].MCS, Specifies which FPC/mux block monitor output signal is to be used for LAM block
 */
typedef enum
{
    IfxIom_LamMonitorInputChannel_0 = 0,      /**< \brief Specifies 0 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_1,          /**< \brief Specifies 1 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_2,          /**< \brief Specifies 2 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_3,          /**< \brief Specifies 3 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_4,          /**< \brief Specifies 4 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_5,          /**< \brief Specifies 5 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_6,          /**< \brief Specifies 6 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_7,          /**< \brief Specifies 7 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_8,          /**< \brief Specifies 8 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_9,          /**< \brief Specifies 9 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_10,         /**< \brief Specifies 10 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_11,         /**< \brief Specifies 11 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_12,         /**< \brief Specifies 12 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_13,         /**< \brief Specifies 13 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_14,         /**< \brief Specifies 14 FPC/mux block monitor output signal is to be used for LAM block  */
    IfxIom_LamMonitorInputChannel_15          /**< \brief Specifies 15 FPC/mux block monitor output signal is to be used for LAM block  */
} IfxIom_LamMonitorInputChannel;

/** \brief LAMCFG[lamId].MOS, Specifies whether the monitor signal from the FPC monitor channel is sourced directly or compared with the reference signal from the FPC reference channel for the event compare.
 */
typedef enum
{
    IfxIom_LamMonitorSource_directFpcMonitor = 0,  /**< \brief Monitor signal is sourced directly from FPC monitor channel. */
    IfxIom_LamMonitorSource_exoredFpcMonitor = 1   /**< \brief Monitor signal is EXORed with FPC reference channel. */
} IfxIom_LamMonitorSource;

/** \brief LAMCFG[lamId].RCS, Specifies which FPC/mux block reference output signal is to be used for LAM block
 */
typedef enum
{
    IfxIom_LamReferenceInputChannel_0 = 0,      /**< \brief Specifies 0 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_1,          /**< \brief Specifies 1 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_2,          /**< \brief Specifies 2 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_3,          /**< \brief Specifies 3 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_4,          /**< \brief Specifies 4 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_5,          /**< \brief Specifies 5 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_6,          /**< \brief Specifies 6 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_7,          /**< \brief Specifies 7 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_8,          /**< \brief Specifies 8 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_9,          /**< \brief Specifies 9 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_10,         /**< \brief Specifies 10 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_11,         /**< \brief Specifies 11 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_12,         /**< \brief Specifies 12 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_13,         /**< \brief Specifies 13 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_14,         /**< \brief Specifies 14 FPC/mux block reference output signal is to be used for LAM block  */
    IfxIom_LamReferenceInputChannel_15          /**< \brief Specifies 15 FPC/mux block reference output signal is to be used for LAM block  */
} IfxIom_LamReferenceInputChannel;

/** \brief LAMCFG[lamId].RMS, Specifies whether the event window generation is free-running or gated with the monitor or reference.
 */
typedef enum
{
    IfxIom_LamRunMode_freeRunning = 0,  /**< \brief Specifies event window generation is free-running. */
    IfxIom_LamRunMode_gated       = 1   /**< \brief Specifies event window generation is gated with the monitor or
                                         * reference signal. */
} IfxIom_LamRunMode;

/** \brief FPCCTR[channelId].ISM, Specifies the monitor signal input for Filter & Prescaler cell
 */
typedef enum
{
    IfxIom_MonitorSignal_portLogic = 0,  /**< \brief Specifies the specific pad pins as monitor signal */
    IfxIom_MonitorSignal_0         = 1,  /**< \brief Specifies the monitor signal 0  */
    IfxIom_MonitorSignal_1,              /**< \brief Specifies the monitor signal 1  */
    IfxIom_MonitorSignal_2               /**< \brief Specifies the monitor signal 2  */
} IfxIom_MonitorSignal;

/** \brief FPCCTR[channelId].ISR,Specifies the reference signal input for Filter & Prescaler cell
 */
typedef enum
{
    IfxIom_ReferenceSignal_portLogic = 0,       /**< \brief Specifies the specific pad pins as reference signal */
    IfxIom_ReferenceSignal_0         = 1,       /**< \brief Specifies the reference signal 0  */
    IfxIom_ReferenceSignal_1,                   /**< \brief Specifies the reference signal 1  */
    IfxIom_ReferenceSignal_2,                   /**< \brief Specifies the reference signal 2  */
    IfxIom_ReferenceSignal_gtmEXORCombiner = 4  /**< \brief Specifies the GTM EXOR Combiner pins */
} IfxIom_ReferenceSignal;

/** \brief Enable/disable the sensitivity of the module to sleep signal\n
 * Definition in Ifx_IOM.CLC.B.EDIS
 */
typedef enum
{
    IfxIom_SleepMode_enable  = 0, /**< \brief enables sleep mode */
    IfxIom_SleepMode_disable = 1  /**< \brief disables sleep mode */
} IfxIom_SleepMode;

/** \} */

/** \brief Specifies the Logic Module Analyser Module Number
 */
typedef enum
{
    IfxIom_LamId_0 = 0,      /**< \brief Specifies the LAM Id 0  */
    IfxIom_LamId_1,          /**< \brief Specifies the LAM Id 1  */
    IfxIom_LamId_2,          /**< \brief Specifies the LAM Id 2  */
    IfxIom_LamId_3,          /**< \brief Specifies the LAM Id 3  */
    IfxIom_LamId_4,          /**< \brief Specifies the LAM Id 4  */
    IfxIom_LamId_5,          /**< \brief Specifies the LAM Id 5  */
    IfxIom_LamId_6,          /**< \brief Specifies the LAM Id 6  */
    IfxIom_LamId_7,          /**< \brief Specifies the LAM Id 7  */
    IfxIom_LamId_8,          /**< \brief Specifies the LAM Id 8  */
    IfxIom_LamId_9,          /**< \brief Specifies the LAM Id 9  */
    IfxIom_LamId_10,         /**< \brief Specifies the LAM Id 10  */
    IfxIom_LamId_11,         /**< \brief Specifies the LAM Id 11  */
    IfxIom_LamId_12,         /**< \brief Specifies the LAM Id 12  */
    IfxIom_LamId_13,         /**< \brief Specifies the LAM Id 13  */
    IfxIom_LamId_14,         /**< \brief Specifies the LAM Id 14  */
    IfxIom_LamId_15          /**< \brief Specifies the LAM Id 15  */
} IfxIom_LamId;

/** \addtogroup IfxLld_Iom_Std_Module
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Enable the IOM module control
 * \param iom pointer to IOM module registers
 * \return None
 */
IFX_INLINE void IfxIom_enableModule(Ifx_IOM *iom);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Reset the IOM module
 * \param iom pointer to IOM module registers
 * \return None
 */
IFX_EXTERN void IfxIom_resetModule(Ifx_IOM *iom);

/** \} */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Enable/disable the sensitivity of the module to sleep signal
 * \param iom pointer to IOM registers
 * \param mode mode selection (enable/disable)
 * \return None
 */
IFX_INLINE void IfxIom_setSleepMode(Ifx_IOM *iom, IfxIom_SleepMode mode);

/**
 * \param iom pointer to IOM register space
 * \return the last generated event
 */
IFX_INLINE uint16 IfxIom_eventTriggerHistory(Ifx_IOM *iom);

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE void IfxIom_enableModule(Ifx_IOM *iom)
{
    iom->CLC.B.DISR = 0;
}


IFX_INLINE void IfxIom_setSleepMode(Ifx_IOM *iom, IfxIom_SleepMode mode)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(passwd);
    iom->CLC.B.EDIS = mode;
    IfxScuWdt_setCpuEndinit(passwd);
}


IFX_INLINE uint16 IfxIom_eventTriggerHistory(Ifx_IOM *iom)
{
    uint16 tempECMETH0;

    tempECMETH0 = (uint16)iom->ECMETH0.U;
    return tempECMETH0;
}


#endif /* IFXIOM_H */
