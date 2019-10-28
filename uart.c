#include "uart.h"
#include "gpio_regs.h"
#include "uart_regs.h"
#include "irq.h"
#include "matrix.h"

static char img_buffer[384];

void uart_init() {
    // enable UART0 clock
    SIM_SCGC4 |= 0x00000400;
    SIM_SOPT2 &= 0xF3FFFFFF;
    SIM_SOPT2 |= 0x04010000;

    // disable UART0
    UART0_C2 = 0x00;
    // set baudrate to 38400 (SBR = 25)
    UART0_BDH = 0x00;
    UART0_BDL = 0x19;
    // oversampling set to 25 (OSR = 25)
    UART0_C4 = 0x18;
    // no parity, no interrupt (poll mode)
    UART0_C1 = 0x00;
    UART0_C3 = 0x0C;
    UART0_C5 = 0x00;

    // enable PORTA clock for RX/TX
    SIM_SCGC5 |= 0x00000200;
    // set pins PTA1 and PTA2 as UART
    PORTA_PCR1 = 0x00000200;
    PORTA_PCR2 = 0x00000200;
    // read UART0 data register to empty the buffer
    UART0_D;
    // clear error flags
    UART0_S1 = 0x0A;
    // enable UART0 with interrupt on receive
    UART0_C2 = 0x2C;
    // access stored image while receiving bytes
    uart_image = (rgb_color *) img_buffer;

    irq_enable(UART0_IRQ_NUM);
    irq_set_priority(UART0_IRQ_NUM, IRQ_PRIORITY_HIGH);
}

void uart_putchar(char c) {
    // wait while transmit buffer is full
    while(!(UART0_S1&0x80));
    // send the char
    UART0_D = c;
}

unsigned char uart_getchar() {
    // clear error flags
    UART0_S1 = 0x0A;
    // wait until receive buffer is full
    while(!(UART0_S1&0x20));
    return UART0_D;
}

void uart_puts(const char *s) {
    int i = 0;
    while(s[i] != 0) {
        uart_putchar(s[i]);
        i++;
    }
    uart_putchar('\n');
}

void uart_gets(char *s, int size) {
    int i=0;
    for(; i<size-1; i++) {
        s[i] = uart_getchar();
        if(s[i] == '\n' || s[i] == '\r') {
            i++;
            break;
        }
    }
    s[i] = 0;
}

/* when a byte is received */
void UART0_IRQHandler() {
    static int counter = -1;
    static int offset = 192;
    // detect overrun or framing error
    if(UART0_S1 & 0x0A) {
        UART0_S1 = 0x0A;
        counter = -1; // wait until next frame start
    } else {
        unsigned char data = uart_getchar();
        if(data == 0xFF)
            counter = 0;
        else if(counter >= 0 && counter < 192)
            img_buffer[offset + counter++] = data;
        // when a full frame is received, display it and start filling the other part
        if(counter >= 192) {
            uart_image = (rgb_color *) &img_buffer[offset];
            offset = offset ? 0 : 192;
            counter = -1;
        }
    }
}
