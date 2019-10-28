#include "led.h"
#include "gpio_regs.h"

#define PTD5_SET 0x00000020
#define PTE29_SET 0x20000000

/* initialize both LEDs */
void led_init() {
    green_led_init();
    red_led_init();
}

/* initialize GPIO for green LED */
void green_led_init() {
    // enable PORTD clock
    SIM_SCGC5 |= 0x00001000;
    // set pins PTD5 as GPIO
    PORTD_PCR5 = PCR_GPIO_MASK;
    // set PTD5 as output
    GPIOD_PDDR |= PTD5_SET;
    // turn on PTD5
    GPIOD_PCOR = PTD5_SET;
}

/* initialize GPIO for red LED */
void red_led_init() {
    // enable PORTE clock
    SIM_SCGC5 |= 0x00002000;
    // set pin PTE29 as GPIO
    PORTE_PCR29 = PCR_GPIO_MASK;
    // set PTE29 as output
    GPIOE_PDDR |= PTE29_SET;
    // turn on PTE29
    GPIOE_PCOR = PTE29_SET;
}

/* turn on the green LED */
void green_led_on(){
    // turn on PTD5
    GPIOD_PCOR = PTD5_SET;
}
/* turn off the green LED */
void green_led_off(){
    // turn off PTD5
    GPIOD_PSOR = PTD5_SET;
}
/* toggle green LED state */
void green_led_toggle() {
    // turn on PTD5
    GPIOD_PTOR = PTD5_SET;
}
/* turn on the red LED */
void red_led_on(){
    // turn on PTE29
    GPIOE_PCOR = PTE29_SET;
}
/* turn off the red LED */
void red_led_off() {
    // turn off PTE29
    GPIOE_PSOR = PTE29_SET;
}
/* toggle red LED state */
void red_led_toggle() {
    // toggle PTE29
    GPIOE_PTOR = PTE29_SET;
}
