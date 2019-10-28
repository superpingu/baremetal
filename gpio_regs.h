#include <stdint.h>
/* This file contains the definition of registers related to GPIO use */

#ifndef GPIO_REGS_H
#define GPIO_REGS_H

// clock enable
#define SIM_SCGC5 (*(volatile uint32_t *) 0x40048038)

// pin control
#define PORTA_PCR0 (*(volatile uint32_t *) 0x40049000)
#define PORTA_PCR1 (*(volatile uint32_t *) 0x40049004)
#define PORTA_PCR2 (*(volatile uint32_t *) 0x40049008)
#define PORTA_PCR3 (*(volatile uint32_t *) 0x4004900C)
#define PORTA_PCR4 (*(volatile uint32_t *) 0x40049010)
#define PORTA_PCR5 (*(volatile uint32_t *) 0x40049014)
#define PORTA_PCR6 (*(volatile uint32_t *) 0x40049018)
#define PORTA_PCR7 (*(volatile uint32_t *) 0x4004901C)
#define PORTA_PCR8 (*(volatile uint32_t *) 0x40049020)
#define PORTA_PCR9 (*(volatile uint32_t *) 0x40049024)
#define PORTA_PCR10 (*(volatile uint32_t *) 0x40049028)
#define PORTA_PCR11 (*(volatile uint32_t *) 0x4004902C)
#define PORTA_PCR12 (*(volatile uint32_t *) 0x40049030)
#define PORTA_PCR13 (*(volatile uint32_t *) 0x40049034)
#define PORTA_PCR14 (*(volatile uint32_t *) 0x40049038)
#define PORTA_PCR15 (*(volatile uint32_t *) 0x4004903C)

#define PORTB_PCR0 (*(volatile uint32_t *) 0x4004A000)
#define PORTB_PCR1 (*(volatile uint32_t *) 0x4004A004)
#define PORTB_PCR2 (*(volatile uint32_t *) 0x4004A008)
#define PORTB_PCR3 (*(volatile uint32_t *) 0x4004A00C)
#define PORTB_PCR4 (*(volatile uint32_t *) 0x4004A010)
#define PORTB_PCR5 (*(volatile uint32_t *) 0x4004A014)
#define PORTB_PCR6 (*(volatile uint32_t *) 0x4004A018)
#define PORTB_PCR7 (*(volatile uint32_t *) 0x4004A01C)
#define PORTB_PCR8 (*(volatile uint32_t *) 0x4004A020)
#define PORTB_PCR9 (*(volatile uint32_t *) 0x4004A024)
#define PORTB_PCR10 (*(volatile uint32_t *) 0x4004A028)
#define PORTB_PCR11 (*(volatile uint32_t *) 0x4004A02C)
#define PORTB_PCR12 (*(volatile uint32_t *) 0x4004A030)
#define PORTB_PCR13 (*(volatile uint32_t *) 0x4004A034)
#define PORTB_PCR14 (*(volatile uint32_t *) 0x4004A038)
#define PORTB_PCR15 (*(volatile uint32_t *) 0x4004A03C)

#define PORTC_PCR0 (*(volatile uint32_t *) 0x4004B000)
#define PORTC_PCR1 (*(volatile uint32_t *) 0x4004B004)
#define PORTC_PCR2 (*(volatile uint32_t *) 0x4004B008)
#define PORTC_PCR3 (*(volatile uint32_t *) 0x4004B00C)
#define PORTC_PCR4 (*(volatile uint32_t *) 0x4004B010)
#define PORTC_PCR5 (*(volatile uint32_t *) 0x4004B014)
#define PORTC_PCR6 (*(volatile uint32_t *) 0x4004B018)
#define PORTC_PCR7 (*(volatile uint32_t *) 0x4004B01C)
#define PORTC_PCR8 (*(volatile uint32_t *) 0x4004B020)
#define PORTC_PCR9 (*(volatile uint32_t *) 0x4004B024)
#define PORTC_PCR10 (*(volatile uint32_t *) 0x4004B028)
#define PORTC_PCR11 (*(volatile uint32_t *) 0x4004B02C)
#define PORTC_PCR12 (*(volatile uint32_t *) 0x4004B030)
#define PORTC_PCR13 (*(volatile uint32_t *) 0x4004B034)
#define PORTC_PCR14 (*(volatile uint32_t *) 0x4004B038)
#define PORTC_PCR15 (*(volatile uint32_t *) 0x4004B03C)

#define PORTD_PCR0 (*(volatile uint32_t *) 0x4004C000)
#define PORTD_PCR1 (*(volatile uint32_t *) 0x4004C004)
#define PORTD_PCR2 (*(volatile uint32_t *) 0x4004C008)
#define PORTD_PCR3 (*(volatile uint32_t *) 0x4004C00C)
#define PORTD_PCR4 (*(volatile uint32_t *) 0x4004C010)
#define PORTD_PCR5 (*(volatile uint32_t *) 0x4004C014)
#define PORTD_PCR6 (*(volatile uint32_t *) 0x4004C018)
#define PORTD_PCR7 (*(volatile uint32_t *) 0x4004C01C)
#define PORTD_PCR8 (*(volatile uint32_t *) 0x4004C020)
#define PORTD_PCR9 (*(volatile uint32_t *) 0x4004C024)
#define PORTD_PCR10 (*(volatile uint32_t *) 0x4004C028)
#define PORTD_PCR11 (*(volatile uint32_t *) 0x4004C02C)
#define PORTD_PCR12 (*(volatile uint32_t *) 0x4004C030)
#define PORTD_PCR13 (*(volatile uint32_t *) 0x4004C034)
#define PORTD_PCR14 (*(volatile uint32_t *) 0x4004C038)
#define PORTD_PCR15 (*(volatile uint32_t *) 0x4004C03C)

#define PORTE_PCR29 (*(volatile uint32_t *) 0x4004D074)

// pin control registers masks
#define PCR_GPIO_MASK 0x00000100
#define PCR_PULLUP_MASK 0x00000003
#define PCR_PULLDOWN_MASK 0x00000002
#define PCR_INTRISING_MASK 0x00090000
#define PCR_INTFALLING_MASK 0x000A0000
#define PCR_ISF_MASK 0x01000000

// port output registers
#define GPIOA_PDOR (*(volatile uint32_t *) 0x400FF000)
#define GPIOB_PDOR (*(volatile uint32_t *) 0x400FF040)
#define GPIOC_PDOR (*(volatile uint32_t *) 0x400FF080)
#define GPIOD_PDOR (*(volatile uint32_t *) 0x400FF0C0)
#define GPIOE_PDOR (*(volatile uint32_t *) 0x400FF100)

// port set output registers
#define GPIOA_PSOR (*(volatile uint32_t *) 0x400FF004)
#define GPIOB_PSOR (*(volatile uint32_t *) 0x400FF044)
#define GPIOC_PSOR (*(volatile uint32_t *) 0x400FF084)
#define GPIOD_PSOR (*(volatile uint32_t *) 0x400FF0C4)
#define GPIOE_PSOR (*(volatile uint32_t *) 0x400FF104)

// port clear output registers
#define GPIOA_PCOR (*(volatile uint32_t *) 0x400FF008)
#define GPIOB_PCOR (*(volatile uint32_t *) 0x400FF048)
#define GPIOC_PCOR (*(volatile uint32_t *) 0x400FF088)
#define GPIOD_PCOR (*(volatile uint32_t *) 0x400FF0C8)
#define GPIOE_PCOR (*(volatile uint32_t *) 0x400FF108)

// port toggle output registers
#define GPIOA_PTOR (*(volatile uint32_t *) 0x400FF00C)
#define GPIOB_PTOR (*(volatile uint32_t *) 0x400FF04C)
#define GPIOC_PTOR (*(volatile uint32_t *) 0x400FF08C)
#define GPIOD_PTOR (*(volatile uint32_t *) 0x400FF0CC)
#define GPIOE_PTOR (*(volatile uint32_t *) 0x400FF10C)

// port data input registers
#define GPIOA_PDIR (*(volatile uint32_t *) 0x400F010)
#define GPIOB_PDIR (*(volatile uint32_t *) 0x400F050)
#define GPIOC_PDIR (*(volatile uint32_t *) 0x400F090)
#define GPIOD_PDIR (*(volatile uint32_t *) 0x400F0D0)
#define GPIOE_PDIR (*(volatile uint32_t *) 0x400FF110)

// port data direction registers
#define GPIOA_PDDR (*(volatile uint32_t *) 0x400FF014)
#define GPIOB_PDDR (*(volatile uint32_t *) 0x400FF054)
#define GPIOC_PDDR (*(volatile uint32_t *) 0x400FF094)
#define GPIOD_PDDR (*(volatile uint32_t *) 0x400FF0D4)
#define GPIOE_PDDR (*(volatile uint32_t *) 0x400FF114)

// GPIO MASKS
#define PTx0_MASK 0x0001
#define PTx1_MASK 0x0002
#define PTx2_MASK 0x0004
#define PTx3_MASK 0x0008
#define PTx4_MASK 0x0010
#define PTx5_MASK 0x0020
#define PTx6_MASK 0x0040
#define PTx7_MASK 0x0080
#define PTx8_MASK 0x0100
#define PTx9_MASK 0x0200
#define PTx10_MASK 0x0400
#define PTx11_MASK 0x0800
#define PTx12_MASK 0x1000
#define PTx13_MASK 0x2000
#define PTx14_MASK 0x4000
#define PTx15_MASK 0x8000


#endif
