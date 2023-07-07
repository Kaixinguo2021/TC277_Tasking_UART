/*
 * Main.h
 *
 */
#ifndef SYSTEM_MAIN
#define SYSTEM_MAIN

#include "Cpu/Std/Ifx_Types.h"
#include "Cpu/Std/IfxCpu.h"
#include "Scu/Std/IfxScuWdt.h"

#include "Port\Io\IfxPort_Io.h"
#include "Stm\Std\IfxStm.h"
#include <Asclin/Asc/IfxAsclin_Asc.h>

void UART_Init(void);
IfxAsclin_Asc* UART_GetHandle(void);
void UART_WriteByte(uint8 data);
void UART_Write(uint8 *p_data, Ifx_SizeT count);

#endif
