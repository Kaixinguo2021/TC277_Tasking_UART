/*
 * ASC.c
 *
 */
#include "../Main/main.h"
// used globally
#define IFX_INTPRIO_ASCLIN0_TX    34
#define IFX_INTPRIO_ASCLIN0_RX    35
#define IFX_INTPRIO_ASCLIN0_ER    36
#define ASC_TX_BUFFER_SIZE 64
#define ASC_RX_BUFFER_SIZE 64
static IfxAsclin_Asc asc;

static uint8 ascTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 ascRxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

// pin configuration
const IfxAsclin_Asc_Pins uart_pins = {
		NULL,                       IfxPort_InputMode_pullUp,    // CTS pin not used
		&IfxAsclin0_RXA_P14_1_IN,   IfxPort_InputMode_pullUp,    // Rx pin
		NULL,                       IfxPort_OutputMode_pushPull, // RTS pin not used
		&IfxAsclin0_TX_P14_0_OUT,   IfxPort_OutputMode_pushPull, // Tx pin
		IfxPort_PadDriver_cmosAutomotiveSpeed4
};
void UART_Init(void)
{
	// create module config
	IfxAsclin_Asc_Config ascConfig;

	IfxAsclin_Asc_initModuleConfig(&ascConfig, &MODULE_ASCLIN0);
	// set the desired baudrate
	ascConfig.baudrate.prescaler = 1;
	ascConfig.baudrate.baudrate = 9600; // FDR values will be calculated in initModule

	ascConfig.frame.frameMode  = IfxAsclin_FrameMode_asc;
	ascConfig.frame.dataLength = IfxAsclin_DataLength_8;
	ascConfig.frame.stopBit = IfxAsclin_StopBit_1;
	ascConfig.frame.shiftDir = IfxAsclin_ShiftDirection_lsbFirst;
	ascConfig.frame.parityBit = FALSE;

	// ISR priorities and interrupt target
	ascConfig.interrupt.txPriority = IFX_INTPRIO_ASCLIN0_TX;
    ascConfig.interrupt.rxPriority = IFX_INTPRIO_ASCLIN0_RX;
    ascConfig.interrupt.erPriority = IFX_INTPRIO_ASCLIN0_ER;
	ascConfig.interrupt.typeOfService =   IfxSrc_Tos_cpu0;

	// FIFO configuration
	ascConfig.txBuffer = &ascTxBuffer;
	ascConfig.txBufferSize = ASC_TX_BUFFER_SIZE;
	ascConfig.rxBuffer = &ascRxBuffer;
	ascConfig.rxBufferSize = ASC_RX_BUFFER_SIZE;

	ascConfig.pins = &uart_pins;
	// initialize module
	IfxAsclin_Asc_initModule(&asc, &ascConfig);
}
IfxAsclin_Asc* UART_GetHandle(void)
{
	return &asc;
}
void UART_WriteByte(uint8 data)
{
	IfxAsclin_Asc_blockingWrite(&asc, data);
}

void UART_Write(uint8 *p_data, Ifx_SizeT count)
{
	uint8 *p_send = p_data;

	if(count > 0)
		IfxAsclin_Asc_write(&asc, p_data, &count, TIME_INFINITE);
	else
	{
		while(*p_send != (uint8)'\0')
			UART_WriteByte(*p_send++);
	}
}

IFX_INTERRUPT(asclin0TxISR, 0, IFX_INTPRIO_ASCLIN0_TX)
{

	IfxAsclin_Asc_isrTransmit(UART_GetHandle());

}

uint8 IfxAsclin_Asc_Receive(IfxAsclin_Asc *asclin)
{
    uint8 ascData=0;

    switch (asclin->dataBufferMode)
    {
    case Ifx_DataBufferMode_normal:
    {
        /* FIXME optimize usage of HW fifo */
        /* FIXME add support for data size != 8 bit */
        IfxAsclin_read8(asclin->asclin, &ascData, 1);


        if (Ifx_Fifo_write(asclin->rx, &ascData, 1, TIME_NULL) != 0)
        {
            /* Receive buffer is full, data is discard */
            asclin->rxSwFifoOverflow = TRUE;
        }

        break;
    }
    case Ifx_DataBufferMode_timeStampSingle:
    {
        Ifx_DataBufferMode_TimeStampSingle packedData;

        packedData.timestamp = now();
        IfxAsclin_read8(asclin->asclin, &ascData, 1);
        packedData.data      = ascData;

        if (Ifx_Fifo_write(asclin->rx, &packedData, sizeof(packedData), TIME_NULL) != 0)
        {
            /* Receive buffer is full, data is discard */
            asclin->rxSwFifoOverflow = TRUE;
        }
    }
    break;
    }
    return ascData;
}
IFX_INTERRUPT(asclin0RxISR, 0, IFX_INTPRIO_ASCLIN0_RX)
{

	UART_WriteByte(IfxAsclin_Asc_Receive(UART_GetHandle()));
}

IFX_INTERRUPT(asclin0ErISR, 0, IFX_INTPRIO_ASCLIN0_ER)
{

	IfxAsclin_Asc_isrError(UART_GetHandle());

}
