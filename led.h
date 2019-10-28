#ifndef LED_H
#define LED_H

#include "led.h"
#include "gpio_regs.h"

/* initialize both LEDs */
void led_init();
/* initialize GPIO for green LED */
void green_led_init();
/* initialize GPIO for red LED */
void red_led_init();

/* turn on the green LED */
void green_led_on();
/* turn off the green LED */
void green_led_off();
/* toggle green LED state */
void green_led_toggle();
/* turn on the red LED */
void red_led_on();
/* turn off the red LED */
void red_led_off();
/* toggle red LED state */
void red_led_toggle();

#endif
