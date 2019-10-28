#include "pit.h"
#include "irq.h"
#include "matrix.h"

/* clock enable */
#define SIM_SCGC6 (*(volatile uint32_t *) 0x4004803C)
/* PIT registers */
#define PIT_MCR (*(volatile uint32_t *) 0x40037000)
#define PIT_LDVAL0 (*(volatile uint32_t *) 0x40037100)
#define PIT_TCTRL0 (*(volatile uint32_t *) 0x40037108)
#define PIT_TFLG0 (*(volatile uint32_t *) 0x4003710C)

void pit_init() {
    // enable clock to the PIT module
    SIM_SCGC6 |= 0x00800000;
    // enable PIT clock
    PIT_MCR = 0x00;
    // 1.7ms period (about 73 fps)
    PIT_LDVAL0 = 40800;
    // clear interrupt flag
    PIT_TFLG0 = 0x01;
    // enable PIT 0 and timer interrupt
    PIT_TCTRL0 = 0x03;

    irq_enable(PIT_IRQ_NUM);
    irq_set_priority(PIT_IRQ_NUM, IRQ_PRIORITY_LOW);
}

/* called every 1.7ms */
void PIT_IRQHandler() {
    static int counter = 0;

    if(counter&0xF8)
        counter = 0;
    mat_set_row(counter, &uart_image[counter*8]);
    counter++;

    // clear interrupt flag
    PIT_TFLG0 = 0x01;
}
