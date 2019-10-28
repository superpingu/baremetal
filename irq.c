#include "irq.h"
#include <stdint.h>

/* useful interrupt registers */
#define VTOR (*(volatile uint32_t *) 0xE000ED08)
#define NVIC_ISER (*(volatile uint32_t *) 0xE000E100)
#define NVIC_ICER (*(volatile uint32_t *) 0xE000E180)
#define NVIC_IPR0 (*(volatile uint32_t *) 0xE000E400)

/* default handler */
#define HANDLER(x) void __attribute__((weak)) x () { disable_irq(); while(1); }

HANDLER(NMI_Handler)
HANDLER(HardFault_Handler)
HANDLER(SVC_Handler)
HANDLER(PendSV_Handler)
HANDLER(SysTick_Handler)
HANDLER(DMA0_IRQHandler)
HANDLER(DMA1_IRQHandler)
HANDLER(DMA2_IRQHandler)
HANDLER(DMA3_IRQHandler)
HANDLER(FTFA_IRQHandler)
HANDLER(PMC_IRQHandler)
HANDLER(LLWU_IRQHandler)
HANDLER(I2C0_IRQHandler)
HANDLER(I2C1_IRQHandler)
HANDLER(SPI0_IRQHandler)
HANDLER(SPI1_IRQHandler)
HANDLER(UART0_IRQHandler)
HANDLER(UART1_IRQHandler)
HANDLER(UART2_IRQHandler)
HANDLER(ADC0_IRQHandler)
HANDLER(CMP0_IRQHandler)
HANDLER(TMP0_IRQHandler)
HANDLER(TMP1_IRQHandler)
HANDLER(TMP2_IRQHandler)
HANDLER(RTC0_IRQHandler)
HANDLER(RTC1_IRQHandler)
HANDLER(PIT_IRQHandler)
HANDLER(I2S0_IRQHandler)
HANDLER(USBOTG_IRQHandler)
HANDLER(DAC0_IRQHandler)
HANDLER(TSI0_IRQHandler)
HANDLER(MCG_IRQHandler)
HANDLER(LPTMR0_IRQHandler)
HANDLER(SLCD_IRQHandler)
HANDLER(PCM0_IRQHandler)
HANDLER(PCM1_IRQHandler)

void _start(void);
extern char _stackstart;

static void * vector_table[] __attribute__((section(".irq"))) = {
    // Stack and Reset Handler
    (void *) &_stackstart, /* Top of stack */
    _start,             /* Reset handler */

    // ARM internal exceptions
    NMI_Handler,        /* NMI handler */
    HardFault_Handler,  /* Hard Fault handler */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    SVC_Handler,        /* SVC handler */
    0,                  /* Reserved */
    0,                  /* Reserved */
    PendSV_Handler,     /* Pending SVC handler */
    SysTick_Handler,    /* SysTick hanlder */

    // KL46 External interrupts
    DMA0_IRQHandler,         /* DMA0 interrupt */
    DMA1_IRQHandler,         /* DMA1 interrupt */
    DMA2_IRQHandler,         /* DMA2 interrupt */
    DMA3_IRQHandler,         /* DMA3 interrupt */
    0,                       /* Reserved */
    FTFA_IRQHandler,         /* FTFA interrupt */
    PMC_IRQHandler,          /* PMC interrupt */
    LLWU_IRQHandler,         /* LLWU interrupt */
    I2C0_IRQHandler,         /* I2C 0 interrupt */
    I2C1_IRQHandler,         /* I2C 1 interrupt */
    SPI0_IRQHandler,         /* SPI 0 interrupt */
    SPI1_IRQHandler,         /* SPI 1 interrupt */
    UART0_IRQHandler,        /* UART 0 interrupt */
    UART1_IRQHandler,        /* UART 1 interrupt */
    UART2_IRQHandler,        /* UART 2 interrupt */
    ADC0_IRQHandler,         /* ADC 0 interrupt */
    CMP0_IRQHandler,         /* CMP 0 interrupt */
    TMP0_IRQHandler,         /* TMP 0 interrupt */
    TMP1_IRQHandler,         /* TMP 1 interrupt */
    TMP2_IRQHandler,         /* TMP2 interrupt */
    RTC0_IRQHandler,         /* RTC0 interrupt */
    RTC1_IRQHandler,         /* RTC1 interrupt */
    PIT_IRQHandler,          /* PIT interrupt */
    I2S0_IRQHandler,         /* I2S0 interrupt */
    USBOTG_IRQHandler,       /* UTBOTG interrupt */
    DAC0_IRQHandler,         /* DAC 0 interrupt */
    TSI0_IRQHandler,         /* TSI 0 interrupt */
    MCG_IRQHandler,          /* MCG interrupt */
    LPTMR0_IRQHandler,       /* LPTMR0 interrupt */
    SLCD_IRQHandler,         /* SLCD interrupt */
    PCM0_IRQHandler,         /* Pin detect (port A) interrupt */
    PCM1_IRQHandler          /* Pin detect (Port C and D) interrupt */
};

/* init interrupts : set interrupt vector to the vector table */
void irq_init(void) {
    VTOR = (uint32_t) &vector_table;
}

/* enable the given external interrupt (interrupt #irq_number) */
void irq_enable(int irq_number) {
    NVIC_ISER = 1 << irq_number;
}

/* disable the given external interrupt (interrupt #irq_number) */
void irq_disable(int irq_number) {
    NVIC_ICER = 1 << irq_number;
}

/* set external interrupt priority (lower value means higher priority) */
void irq_set_priority(int irq_number, unsigned char priority) {
    char * priorities = (char*) &NVIC_IPR0;
    priorities[irq_number] = priority;
}
