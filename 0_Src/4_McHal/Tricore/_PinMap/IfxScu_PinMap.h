/**
 * \file IfxScu_PinMap.h
 * \brief SCU I/O map
 * \ingroup IfxLld_Scu
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
 * \defgroup IfxLld_Scu_pinmap SCU Pin Mapping
 * \ingroup IfxLld_Scu
 */

#ifndef IFXSCU_PINMAP_H
#define IFXSCU_PINMAP_H

#include <_Reg/IfxScu_reg.h>
#include <_Impl/IfxScu_cfg.h>
#include <Port/Std/IfxPort.h>

/** \addtogroup IfxLld_Scu_pinmap
 * \{ */

/** \brief EVR Wakeup pin mapping structure */
typedef const struct
{
    Ifx_SCU*          module;    /**< \brief Base address */
    IfxPort_Pin       pin;       /**< \brief Port pin */
    Ifx_RxSel         select;    /**< \brief Input multiplexer value */
} IfxScu_Evrwup_In;

/** \brief Hardware Configuration pin mapping structure */
typedef const struct
{
    Ifx_SCU*          module;    /**< \brief Base address */
    IfxPort_Pin       pin;       /**< \brief Port pin */
} IfxScu_Hwcfg_In;

/** \brief External Request pin mapping structure */
typedef const struct
{
    Ifx_SCU*          module;    /**< \brief Base address */
    uint8             channelId; /**< \brief ERU Channel ID */
    IfxPort_Pin       pin;       /**< \brief Port pin */
    Ifx_RxSel         select;    /**< \brief Input multiplexer value */
} IfxScu_Req_In;

/** \brief DCDC Sync pin mapping structure */
typedef const struct
{
    Ifx_SCU*          module;    /**< \brief Base address */
    IfxPort_Pin       pin;       /**< \brief Port pin */
    IfxPort_OutputIdx select;    /**< \brief Port control code */
} IfxScu_Dcdcsync_Out;

/** \brief Emergency Stop pin mapping structure */
typedef const struct
{
    Ifx_SCU*          module;    /**< \brief Base address */
    IfxPort_Pin       pin;       /**< \brief Port pin */
    Ifx_RxSel         select;    /**< \brief Input multiplexer value */
} IfxScu_Emgstop_In;

/** \brief Watchdog Timer Lock pin mapping structure */
typedef const struct
{
    Ifx_SCU*          module;    /**< \brief Base address */
    IfxPort_Pin       pin;       /**< \brief Port pin */
    IfxPort_OutputIdx select;    /**< \brief Port control code */
} IfxScu_Wdtlck_Out;

/** \brief External Clock pin mapping structure */
typedef const struct
{
    Ifx_SCU*          module;    /**< \brief Base address */
    IfxPort_Pin       pin;       /**< \brief Port pin */
    IfxPort_OutputIdx select;    /**< \brief Port control code */
} IfxScu_Extclk_Out;

IFX_EXTERN IfxScu_Dcdcsync_Out IfxScu_DCDCSYNC_P32_2_OUT;  /**< \brief SCU_DCDCSYNC: SCU output */
IFX_EXTERN IfxScu_Dcdcsync_Out IfxScu_DCDCSYNC_P33_13_OUT;  /**< \brief SCU_DCDCSYNC: SCU output */
IFX_EXTERN IfxScu_Emgstop_In IfxScu_EMGSTOPA_P33_8_IN;  /**< \brief SCU_EMGSTOPA: SCU input */
IFX_EXTERN IfxScu_Emgstop_In IfxScu_EMGSTOPB_P21_2_IN;  /**< \brief SCU_EMGSTOPB: SCU input */
IFX_EXTERN IfxScu_Evrwup_In IfxScu_EVRWUPA_P14_1_IN;  /**< \brief SCU_EVRWUPA: SCU input */
IFX_EXTERN IfxScu_Evrwup_In IfxScu_EVRWUPB_P15_1_IN;  /**< \brief SCU_EVRWUPB: SCU input */
IFX_EXTERN IfxScu_Extclk_Out IfxScu_EXTCLK0_P23_1_OUT;  /**< \brief SCU_EXTCLK0: SCU output */
IFX_EXTERN IfxScu_Extclk_Out IfxScu_EXTCLK1_P11_12_OUT;  /**< \brief SCU_EXTCLK1: SCU output */
IFX_EXTERN IfxScu_Extclk_Out IfxScu_EXTCLK1_P32_4_OUT;  /**< \brief SCU_EXTCLK1: SCU output */
IFX_EXTERN IfxScu_Hwcfg_In IfxScu_HWCFG0DCLDO_P14_6_IN;  /**< \brief SCU_HWCFG0DCLDO: SCU input   If EVR13 active, latched at cold power on reset to decide between LDO and SMPS mode. */
IFX_EXTERN IfxScu_Hwcfg_In IfxScu_HWCFG1EVR33_P14_5_IN;  /**< \brief SCU_HWCFG1EVR33: SCU input   Latched at cold power on reset to decide EVR33 activation. */
IFX_EXTERN IfxScu_Hwcfg_In IfxScu_HWCFG2EVR13_P14_2_IN;  /**< \brief SCU_HWCFG2EVR13: SCU input   Latched at cold power on reset to decide EVR13 activation. */
IFX_EXTERN IfxScu_Hwcfg_In IfxScu_HWCFG3_BMI_P14_3_IN;  /**< \brief SCU_HWCFG3_BMI: SCU input */
IFX_EXTERN IfxScu_Hwcfg_In IfxScu_HWCFG4_P10_5_IN;  /**< \brief SCU_HWCFG4: SCU input */
IFX_EXTERN IfxScu_Hwcfg_In IfxScu_HWCFG5_P10_6_IN;  /**< \brief SCU_HWCFG5: SCU input */
IFX_EXTERN IfxScu_Hwcfg_In IfxScu_HWCFG6_P14_4_IN;  /**< \brief SCU_HWCFG6: SCU input   Latched at cold power on reset to decide default pad reset state (PU or High-Z). */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ0_P15_4_IN;  /**< \brief SCU_REQ0: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ10_P14_3_IN;  /**< \brief SCU_REQ10: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ11_P20_9_IN;  /**< \brief SCU_REQ11: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ12_P11_10_IN;  /**< \brief SCU_REQ12: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ13_P15_5_IN;  /**< \brief SCU_REQ13: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ14_P02_1_IN;  /**< \brief SCU_REQ14: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ15_P14_1_IN;  /**< \brief SCU_REQ15: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ16_P15_1_IN;  /**< \brief SCU_REQ16: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ1_P15_8_IN;  /**< \brief SCU_REQ1: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ2_P10_2_IN;  /**< \brief SCU_REQ2: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ3_P10_3_IN;  /**< \brief SCU_REQ3: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ4_P10_7_IN;  /**< \brief SCU_REQ4: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ5_P10_8_IN;  /**< \brief SCU_REQ5: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ6_P02_0_IN;  /**< \brief SCU_REQ6: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ7_P00_4_IN;  /**< \brief SCU_REQ7: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ8_P33_7_IN;  /**< \brief SCU_REQ8: SCU input */
IFX_EXTERN IfxScu_Req_In IfxScu_REQ9_P20_0_IN;  /**< \brief SCU_REQ9: SCU input */
IFX_EXTERN IfxScu_Wdtlck_Out IfxScu_WDT0LCK_P20_8_OUT;  /**< \brief SCU_WDT0LCK: SCU output */
IFX_EXTERN IfxScu_Wdtlck_Out IfxScu_WDT1LCK_P20_7_OUT;  /**< \brief SCU_WDT1LCK: SCU output */
IFX_EXTERN IfxScu_Wdtlck_Out IfxScu_WDT2LCK_P20_6_OUT;  /**< \brief SCU_WDT2LCK: SCU output */
IFX_EXTERN IfxScu_Wdtlck_Out IfxScu_WDTSLCK_P20_9_OUT;  /**< \brief SCU_WDTSLCK: SCU output */

/** \brief Table dimensions */
#define IFXSCU_PINMAP_NUM_MODULES 1
#define IFXSCU_PINMAP_NUM_REQUESTS 8
#define IFXSCU_PINMAP_DCDCSYNC_OUT_NUM_ITEMS 2
#define IFXSCU_PINMAP_EMGSTOP_IN_NUM_ITEMS 2
#define IFXSCU_PINMAP_EVRWUP_IN_NUM_ITEMS 2
#define IFXSCU_PINMAP_EXTCLK_OUT_NUM_ITEMS 3
#define IFXSCU_PINMAP_HWCFG_IN_NUM_ITEMS 7
#define IFXSCU_PINMAP_REQ_IN_NUM_ITEMS 4
#define IFXSCU_PINMAP_WDTLCK_OUT_NUM_ITEMS 4


/** \brief IfxScu_Dcdcsync_Out table */
IFX_EXTERN const IfxScu_Dcdcsync_Out *IfxScu_Dcdcsync_Out_pinTable[IFXSCU_PINMAP_NUM_MODULES][IFXSCU_PINMAP_DCDCSYNC_OUT_NUM_ITEMS];

/** \brief IfxScu_Emgstop_In table */
IFX_EXTERN const IfxScu_Emgstop_In *IfxScu_Emgstop_In_pinTable[IFXSCU_PINMAP_NUM_MODULES][IFXSCU_PINMAP_EMGSTOP_IN_NUM_ITEMS];

/** \brief IfxScu_Evrwup_In table */
IFX_EXTERN const IfxScu_Evrwup_In *IfxScu_Evrwup_In_pinTable[IFXSCU_PINMAP_NUM_MODULES][IFXSCU_PINMAP_EVRWUP_IN_NUM_ITEMS];

/** \brief IfxScu_Extclk_Out table */
IFX_EXTERN const IfxScu_Extclk_Out *IfxScu_Extclk_Out_pinTable[IFXSCU_PINMAP_NUM_MODULES][IFXSCU_PINMAP_EXTCLK_OUT_NUM_ITEMS];

/** \brief IfxScu_Hwcfg_In table */
IFX_EXTERN const IfxScu_Hwcfg_In *IfxScu_Hwcfg_In_pinTable[IFXSCU_PINMAP_NUM_MODULES][IFXSCU_PINMAP_HWCFG_IN_NUM_ITEMS];

/** \brief IfxScu_Req_In table */
IFX_EXTERN const IfxScu_Req_In *IfxScu_Req_In_pinTable[IFXSCU_PINMAP_NUM_MODULES][IFXSCU_PINMAP_NUM_REQUESTS][IFXSCU_PINMAP_REQ_IN_NUM_ITEMS];

/** \brief IfxScu_Wdtlck_Out table */
IFX_EXTERN const IfxScu_Wdtlck_Out *IfxScu_Wdtlck_Out_pinTable[IFXSCU_PINMAP_NUM_MODULES][IFXSCU_PINMAP_WDTLCK_OUT_NUM_ITEMS];

/** \} */

#endif /* IFXSCU_PINMAP_H */
