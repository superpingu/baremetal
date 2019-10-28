#include <stdint.h>
/* This file contains the definition of registers related to UART use */

#ifndef UART_REGS_H
#define UART_REGS_H

// UART clock enable
#define SIM_SCGC4 (*(volatile uint32_t *) 0x40048034)
#define SIM_SOPT2 (*(volatile uint32_t *) 0x40048004)

// UART0 Control Registers
#define UART0_C1 (*(volatile uint8_t *) 0x4006A002)
#define UART0_C2 (*(volatile uint8_t *) 0x4006A003)
#define UART0_C3 (*(volatile uint8_t *) 0x4006A006)
#define UART0_C4 (*(volatile uint8_t *) 0x4006A00A)
#define UART0_C5 (*(volatile uint8_t *) 0x4006A00B)

// UART0 baud rate registers
#define UART0_BDH (*(volatile uint8_t *) 0x4006A000)
#define UART0_BDL (*(volatile uint8_t *) 0x4006A001)

// UART0 status registers
#define UART0_S1 (*(volatile uint8_t *) 0x4006A004)
#define UART0_S2 (*(volatile uint8_t *) 0x4006A005)

// UART0 data registers
#define UART0_D (*(volatile uint8_t *) 0x4006A007)

#endif
