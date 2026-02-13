#pragma once

#include <__KCONF.h>
#include <System.h>
#include <Errors.h>

#define UART_COM1Base 0x3F8
#define UART_RegisterData 0             /* Data Register (R/W) */
#define UART_RegisterInterrupt 1        /* Interrupt Enable (R/W) */
#define UART_RegisterFIFOControl 2     /* FIFO Control (W) */
#define UART_RegisterLineControl 3     /* Line Control (R/W) */
#define UART_RegisterModemControl 4    /* Modem Control (R/W) */
#define UART_RegisterLineStatus 5      /* Line Status (R) */
#define UART_RegisterModemStatus 6     /* Modem Status (R) */
#define UART_RegisterScratch 7          /* Scratch Register (R/W) */
#define UART_LSRDataReady 0x01
#define UART_LSRTHREmpty 0x20

int UART_KickStart(SYSTEM_ERROR* Error);
void UART_PutCharacter(char, SYSTEM_ERROR*);
void UART_PutString(const char*, SYSTEM_ERROR*);
uint16_t UART_GetPort(SYSTEM_ERROR*);

