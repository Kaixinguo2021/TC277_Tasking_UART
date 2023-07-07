/**
 * \file QspiTlfDemo.c
 * \brief
 *
 * \version V0.2
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
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
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "TLF35584.h"
#include "Configuration.h"
#include <Qspi/SpiMaster/IfxQspi_SpiMaster.h>

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/
#define TLF_BUFFER_SIZE 1   /**< \brief Tx/Rx Buffer size */

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/
typedef struct
{
    uint32 spiTxBuffer[TLF_BUFFER_SIZE];                               /**< \brief Qspi Transmit buffer */
    uint32 spiRxBuffer[TLF_BUFFER_SIZE];                               /**< \brief Qspi receive buffer */
} AppQspi_TLF_Buffer;

/** \brief QspiCpu global data */
typedef struct
{
    AppQspi_TLF_Buffer qspiBuffer;                       /**< \brief Qspi buffer */
    struct
    {
        IfxQspi_SpiMaster         *spiMaster;            /**< \brief Pointer to spi Master handle */
        IfxQspi_SpiMaster_Channel spiMasterChannel;      /**< \brief Spi Master Channel handle */
    }drivers;
}  App_Qspi_TLF_Cpu;

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
#if TLF_VAR_LOCATION == 0
	#if defined(__GNUC__)
	#pragma section ".bss_cpu0" awc0
	#endif
	#if defined(__TASKING__)
	#pragma section farbss "bss_cpu0"
	#pragma section fardata "data_cpu0"
	#endif
	#if defined(__DCC__)
	#pragma section DATA ".data_cpu0" ".bss_cpu0" far-absolute RW
	#endif
#elif TLF_VAR_LOCATION == 1
	#if defined(__GNUC__)
	#pragma section ".bss_cpu1" awc1
	#endif
	#if defined(__TASKING__)
	#pragma section farbss "bss_cpu1"
	#pragma section fardata "data_cpu1"
	#endif
	#if defined(__DCC__)
	#pragma section DATA ".data_cpu1" ".bss_cpu1" far-absolute RW
	#endif
#elif TLF_VAR_LOCATION == 2
	#if defined(__GNUC__)
	#pragma section ".bss_cpu2" awc2
	#endif
	#if defined(__TASKING__)
	#pragma section farbss "bss_cpu2"
	#pragma section fardata "data_cpu2"
	#endif
	#if defined(__DCC__)
	#pragma section DATA ".data_cpu2" ".bss_cpu2" far-absolute RW
	#endif
#else
#error "Set TLF_VAR_LOCATION to a valid value!"
#endif

App_Qspi_TLF_Cpu g_Qspi_TLF_Cpu;
boolean TLF_A_Step;   // this is the value of DEVCTRL Register which should be different between A and other steps
IfxQspi_SpiMaster *qspi2_init (void);

#if defined(__GNUC__)
#pragma section
#endif
#if defined(__TASKING__)
#pragma section farbss restore
#pragma section fardata restore
#endif
#if defined(__DCC__)
#pragma section DATA RW
#endif

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/
/** \brief TLF (QSPI) initialization
 *
 * This function initializes Qspix in master mode.
 */
void IfxTLF35584_init(void)
{
    /* disable interrupts */
    boolean interruptState = IfxCpu_disableInterrupts();

    g_Qspi_TLF_Cpu.drivers.spiMaster = (IfxQspi_SpiMaster *)TLF_QSPI_INIT();
    IfxQspi_SpiMaster_ChannelConfig spiMasterChannelConfig;

    {
        /* create channel config */
#if defined(__DCC__)
   		// bug on DCC not all bits in mode are cleared
   		memset(&spiMasterChannelConfig, 0, sizeof(spiMasterChannelConfig));
#endif
        IfxQspi_SpiMaster_initChannelConfig(&spiMasterChannelConfig,
            g_Qspi_TLF_Cpu.drivers.spiMaster);

        /* set the baudrate for this channel */
        spiMasterChannelConfig.base.baudrate = 5000000;

        /* set the transfer data width */
        spiMasterChannelConfig.base.mode.dataWidth = 16;

        spiMasterChannelConfig.base.mode.csTrailDelay = 2;
        spiMasterChannelConfig.base.mode.csInactiveDelay = 2;
        spiMasterChannelConfig.base.mode.shiftClock = SpiIf_ShiftClock_shiftTransmitDataOnTrailingEdge;

        const IfxQspi_SpiMaster_Output slsOutput = {&TLF_USE_CHIPSELECT,
                                                    IfxPort_OutputMode_pushPull,
                                                    IfxPort_PadDriver_cmosAutomotiveSpeed1};

        spiMasterChannelConfig.sls.output.pin    = slsOutput.pin;
        spiMasterChannelConfig.sls.output.mode   = slsOutput.mode;
        spiMasterChannelConfig.sls.output.driver = slsOutput.driver;

        /* initialize channel */
        IfxQspi_SpiMaster_initChannel(&g_Qspi_TLF_Cpu.drivers.spiMasterChannel,
            &spiMasterChannelConfig);
    }

    /* init tx buffer area */
	g_Qspi_TLF_Cpu.qspiBuffer.spiTxBuffer[0] = 0;
    g_Qspi_TLF_Cpu.qspiBuffer.spiRxBuffer[0] = 0;

    /* enable interrupts again */
    IfxCpu_restoreInterrupts(interruptState);

    /* first we check for A or B-step of TLF */
    /* we read the value from address 0x34 but ignore the returned value */
    IfxTLF35584_read_write(0x6801);  /* read address 0x34 */
    /* no we read the SPI status flags */
    if ((IfxTLF35584_read_write(0x3E01)>>1) & 0x4)
    {
    	/* there was an address error, this is not the A-step */
    	/* we reset the ADDRE flag */
        IfxTLF35584_read_write(0xBE09);  /* SPISF = 0x04 */
    	TLF_A_Step = FALSE;
    }
    else
    	TLF_A_Step = TRUE;
}

void IfxTLF35584_unprotect_register(void)
{
    IfxTLF35584_read_write(0x8756);  /* PROTCFG = 0xAB */
    IfxTLF35584_read_write(0x87DE);  /* PROTCFG = 0xEF */
    IfxTLF35584_read_write(0x86AD);  /* PROTCFG = 0x56 */
    IfxTLF35584_read_write(0x8625);  /* PROTCFG = 0x12 */
}

void IfxTLF35584_protect_register(void)
{
    IfxTLF35584_read_write(0x87BE);  /* PROTCFG = 0xDF */
    IfxTLF35584_read_write(0x8668);  /* PROTCFG = 0x34 */
    IfxTLF35584_read_write(0x877D);  /* PROTCFG = 0xBE */
    IfxTLF35584_read_write(0x8795);  /* PROTCFG = 0xCA */
}

void IfxTLF35584_disable_window_watchdog(void)
{
    uint32 uiWdcfg0;
	/* first we get the value of WDCFG0 to check the window watchdog */
    if (TLF_A_Step == TRUE)
        uiWdcfg0 = IfxTLF35584_read_write(0x0C00);  /* read WDCFG0 (0x06) */
    else
        uiWdcfg0 = IfxTLF35584_read_write(0x1A00);  /* read RWDCFG0 (0x0D) */
    /* if the WWDEN is cleared then return because the window watchdog is already disabled */
    if (!(uiWdcfg0 & 0x0010)) return;
	/* clear the WWDEN bit */
    uiWdcfg0 &= ~0x0010;
    /* correct the parity */
    if (uiWdcfg0 & 0x0001)
        uiWdcfg0 &= ~0x0001;
    else
        uiWdcfg0 |= 0x0001;
    /* set the write address to 0x06 */
    uiWdcfg0 |= (0x06<<9);
	/* Write back and disable the Window Watchdog */
    IfxTLF35584_read_write(uiWdcfg0);
}

void IfxTLF35584_enable_window_watchdog(void)
{
    uint32 uiWdcfg0;
	/* first we get the value of WDCFG0 to check the window watchdog */
    if (TLF_A_Step == TRUE)
        uiWdcfg0 = IfxTLF35584_read_write(0x0C00);  /* read WDCFG0 (0x06) */
    else
        uiWdcfg0 = IfxTLF35584_read_write(0x1A00);  /* read RWDCFG0 (0x0D) */
    /* if the WWDEN is set then return because the window watchdog is already enabled */
    if (uiWdcfg0 & 0x0010) return;
	/* set the WWDEN bit */
    uiWdcfg0 |= 0x0010;
    /* correct the parity */
    if (uiWdcfg0 & 0x0001)
        uiWdcfg0 &= ~0x0001;
    else
        uiWdcfg0 |= 0x0001;
    /* set the write address to 0x06 */
    uiWdcfg0 |= (0x06<<9);
	/* Write back and enable the Window Watchdog */
    IfxTLF35584_read_write(uiWdcfg0);
}

void IfxTLF35584_disable_err_pin_monitor(void)
{
    uint32 uiSyspcfg;
    if (TLF_A_Step == TRUE)
    {
    	/* first we get the value of SYSPCFG0 to check the error pin monitor */
    	uiSyspcfg = IfxTLF35584_read_write(0x0801);  /* read SYSPCFG0 (0x04) */
        /* if the ERREN is cleared then return because the error pin monitor is already disabled */
        if (!(uiSyspcfg & 0x0004)) return;
    	/* clear the ERREN bit */
        uiSyspcfg &= ~0x0004;
        /* set the write address to 0x04 */
        uiSyspcfg |= (0x04<<9);
        /* parity must not be corrected */
    }
    else
    {
    	/* first we get the value of RSYSPCFG1 to check the error pin monitor */
    	uiSyspcfg = IfxTLF35584_read_write(0x1800);  /* read RSYSPCFG1 (0x0C) */
        /* if the ERREN is cleared then return because the error pin monitor is already disabled */
        if (!(uiSyspcfg & 0x0010)) return;
    	/* clear the ERREN bit */
        uiSyspcfg &= ~0x0010;
        /* set the write address to 0x05 */
        uiSyspcfg |= (0x05<<9);
        /* correct the parity */
        if (uiSyspcfg & 0x0001)
        	uiSyspcfg &= ~0x0001;
        else
        	uiSyspcfg |= 0x0001;
    }
	/* Write back and disable the error pin monitor */
    IfxTLF35584_read_write(uiSyspcfg);
}

void IfxTLF35584_enable_err_pin_monitor(void)
{
    uint32 uiSyspcfg;
    if (TLF_A_Step == TRUE)
    {
    	/* first we get the value of SYSPCFG0 to check the error pin monitor */
    	uiSyspcfg = IfxTLF35584_read_write(0x0801);  /* read SYSPCFG0 (0x04) */
        /* if the ERREN is set then return because the error pin monitor is already enabled */
        if (!(uiSyspcfg & 0x0004)) return;
    	/* set the ERREN bit */
        uiSyspcfg |= 0x0004;
        /* set the write address to 0x04 */
        uiSyspcfg |= (0x04<<9);
        /* parity must not be corrected */
    }
    else
    {
    	/* first we get the value of SYSPCFG1 to check the error pin monitor */
    	uiSyspcfg = IfxTLF35584_read_write(0x1800);  /* read SYSPCFG1 (0x0C) */
        /* if the ERREN is set then return because the error pin monitor is already enabled */
        if (!(uiSyspcfg & 0x0010)) return;
    	/* set the ERREN bit */
        uiSyspcfg |= 0x0010;
        /* set the write address to 0x05 */
        uiSyspcfg |= (0x05<<9);
        /* correct the parity */
        if (uiSyspcfg & 0x0001)
        	uiSyspcfg &= ~0x0001;
        else
        	uiSyspcfg |= 0x0001;
    }
	/* Write back and enable the error pin monitor */
    IfxTLF35584_read_write(uiSyspcfg);
}

void IfxTLF35584_goto_standby_state(void)
{
    if (TLF_A_Step == TRUE)
        IfxTLF35584_read_write(0x9DD9);  /* DEVCTRL = 0xEC */
    else
    {
        IfxTLF35584_read_write(0xABD9);  /* DEVCTRL = 0xEC */
        IfxTLF35584_read_write(0xAC27);  /* DEVCTRLN = ~0xEC */
    }
}

void IfxTLF35584_goto_normal_state(void)
{
    /* Switch TLF to normal state */
    if (TLF_A_Step == TRUE)
        IfxTLF35584_read_write(0x9DD5);  /* DEVCTRL = 0xEA */
    else
    {
        IfxTLF35584_read_write(0xABD5);  /* DEVCTRL = 0xEA */
        IfxTLF35584_read_write(0xAC2B);  /* DEVCTRLN = ~0xEA */
    }
}

uint32 IfxTLF35584_read_write(uint32 send_data)
{
    g_Qspi_TLF_Cpu.qspiBuffer.spiTxBuffer[0] = send_data;

    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_TLF_Cpu.drivers.spiMasterChannel) == SpiIf_Status_busy)  {};

    IfxQspi_SpiMaster_exchange(&g_Qspi_TLF_Cpu.drivers.spiMasterChannel, &g_Qspi_TLF_Cpu.qspiBuffer.spiTxBuffer[0],
        &g_Qspi_TLF_Cpu.qspiBuffer.spiRxBuffer[0], TLF_BUFFER_SIZE);

    /* we wait until our values are read from Qspi */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_TLF_Cpu.drivers.spiMasterChannel) == SpiIf_Status_busy)  {};

    return (g_Qspi_TLF_Cpu.qspiBuffer.spiRxBuffer[0]);

}
