#ifndef IRQ_H
#define IRQ_H

/* global enable/disable interrupts */
#define enable_irq() asm volatile("cpsie i")
#define disable_irq() asm volatile("cpsid i")

/* IRQ numbers (used in irq_enable/irq_disable) */
#define DMA0_IRQ_NUM 0         /* DMA0 interrupt */
#define DMA1_IRQ_NUM 1         /* DMA1 interrupt */
#define DMA2_IRQ_NUM 2         /* DMA2 interrupt */
#define DMA3_IRQ_NUM 3         /* DMA3 interrupt */
#define FTFA_IRQ_NUM 5         /* FTFA interrupt */
#define PMC_IRQ_NUM 6          /* PMC interrupt */
#define LLWU_IRQ_NUM 7         /* LLWU interrupt */
#define I2C0_IRQ_NUM 8         /* I2C 0 interrupt */
#define I2C1_IRQ_NUM 9         /* I2C 1 interrupt */
#define SPI0_IRQ_NUM 10         /* SPI 0 interrupt */
#define SPI1_IRQ_NUM 11         /* SPI 1 interrupt */
#define UART0_IRQ_NUM 12        /* UART 0 interrupt */
#define UART1_IRQ_NUM 13        /* UART 1 interrupt */
#define UART2_IRQ_NUM 14        /* UART 2 interrupt */
#define ADC0_IRQ_NUM 15         /* ADC 0 interrupt */
#define CMP0_IRQ_NUM 16         /* CMP 0 interrupt */
#define TMP0_IRQ_NUM 17         /* TMP 0 interrupt */
#define TMP1_IRQ_NUM 18         /* TMP 1 interrupt */
#define TMP2_IRQ_NUM 19         /* TMP2 interrupt */
#define RTC0_IRQ_NUM 20         /* RTC0 interrupt */
#define RTC1_IRQ_NUM 21         /* RTC1 interrupt */
#define PIT_IRQ_NUM 22          /* PIT interrupt */
#define I2S0_IRQ_NUM 23         /* I2S0 interrupt */
#define USBOTG_IRQ_NUM 24       /* UTBOTG interrupt */
#define DAC0_IRQ_NUM 25         /* DAC 0 interrupt */
#define TSI0_IRQ_NUM 26         /* TSI 0 interrupt */
#define MCG_IRQ_NUM 27          /* MCG interrupt */
#define LPTMR0_IRQ_NUM 28       /* LPTMR0 interrupt */
#define SLCD_IRQ_NUM 29         /* SLCD interrupt */
#define PCM0_IRQ_NUM 30         /* Pin detect (port A) interrupt */
#define PCM1_IRQ_NUM 31         /* Pin detect (Port C and D) interrupt */

/* IRQ available priorities */
#define IRQ_PRIORITY_HIGHER 0x00
#define IRQ_PRIORITY_HIGH 0x40
#define IRQ_PRIORITY_LOW 0x80
#define IRQ_PRIORITY_LOWER 0xC0

/* init interrupts : set interrupt vector to the vector table */
void irq_init(void);

/* enable the given external interrupt (interrupt #irq_number) */
void irq_enable(int irq_number);

/* disable the given external interrupt (interrupt #irq_number) */
void irq_disable(int irq_number);

/* set external interrupt priority (lower value means higher priority) */
void irq_set_priority(int irq_number, unsigned char priority);

#endif
