#include "clocks.h"
#include "gpio_regs.h"

/* system clocks registers */
#define MCG_C1 (*(volatile uint8_t *) 0x40064000)
#define MCG_C2 (*(volatile uint8_t *) 0x40064001)
#define MCG_C3 (*(volatile uint8_t *) 0x40064002)
#define MCG_C4 (*(volatile uint8_t *) 0x40064003)
#define MCG_C5 (*(volatile uint8_t *) 0x40064004)
#define MCG_C6 (*(volatile uint8_t *) 0x40064005)
#define MCG_S (*(volatile uint8_t *) 0x40064006)
#define SIM_CLKDIV1 (*(volatile uint32_t *) 0x40048044)

/* watchdog register */
#define SIM_COPC (*(volatile uint32_t *) 0x40048100)

void clocks_init() {
    //disable watchdog
    SIM_COPC = 0x00;
    // enable PORT A clocks
    SIM_SCGC5 |= 0x0200;

    // change to external clock without PLL or FLL (FBE)
    MCG_C2 = 0x1C;
    // divide factor is 256
    MCG_C1 = 0x98;
    // wait for the external christal to start
    while(!(MCG_S & 0x02));
    // wait until the internal clock is disabled
    while(MCG_S & 0x10);
    // wait until selected clock is external clock
    while((MCG_S & 0x0C) != 0x08);

    // use PLL instead of FLL (switch to PBE)
    // enable PLL, divide by 4
    MCG_C5 = 0x03;
    // select PLL instead of FLL
    MCG_C6 = 0x40;
    // wait for PLL to be selected
    while(!(MCG_S & 0x20));
    // wait for PLL to lock
    while(!(MCG_S & 0x40));

    // engage PLL (PEE)
    // divide factor is 4
    MCG_C1 = 0x10;
    // wait until selected clock is external clock with PLL
    while((MCG_S & 0x0C) != 0x0C);

    // set MCGOUTCLK divide to 1 and peripheral clock divide to 2 (24 Mhz)
    SIM_CLKDIV1 = 0x00010000;
}
