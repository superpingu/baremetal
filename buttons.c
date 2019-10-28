#include "buttons.h"
#include "gpio_regs.h"
#include "irq.h"
#include "led.h"

void button_init() {
    // enable PORTC clock
    SIM_SCGC5 |= 0x00000800;
    // PC3 as GPIO, interrupt on falling edge, pull up enable
    PORTC_PCR3 = PCR_GPIO_MASK | PCR_PULLUP_MASK | PCR_INTFALLING_MASK;
    // make sure PC3 is set as input
    GPIOC_PDDR = GPIOC_PDDR & 0xFFFFFFF7;
    // enable corresponding interrupt
    irq_enable(PCM1_IRQ_NUM);
}

void PCM1_IRQHandler() {
    red_led_toggle();
    PORTC_PCR3 |= PCR_ISF_MASK;
}
