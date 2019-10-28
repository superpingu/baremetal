#include "irq.h"
#include "buttons.h"
#include "pit.h"
#include "led.h"
#include "matrix.h"
#include "uart.h"
#include "clocks.h"

int main() {
    clocks_init();
    irq_init();

    red_led_init();
    button_init();

    uart_init();
    matrix_init();
    init_bank0();
    pit_init();

    enable_irq();

    while(1);
    return 0;
}
