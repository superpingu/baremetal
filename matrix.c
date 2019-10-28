#include "matrix.h"
#include "gpio_regs.h"

#define SB(x) do if(x) GPIOB_PSOR = PTx0_MASK; else GPIOB_PCOR = PTx0_MASK; while(0)
#define LAT(x) do if(x) GPIOB_PSOR = PTx1_MASK; else GPIOB_PCOR = PTx1_MASK; while(0)
#define RST(x) do if(x) GPIOB_PSOR = PTx2_MASK; else GPIOB_PCOR = PTx2_MASK; while(0)

#define SDA(x) do if(x) GPIOC_PSOR = PTx9_MASK; else GPIOC_PCOR = PTx9_MASK; while(0)
#define SCK(x) do if(x) GPIOC_PSOR = PTx8_MASK; else GPIOC_PCOR = PTx8_MASK; while(0)

#define ROW0(x) do if(x) GPIOA_PSOR = PTx13_MASK; else GPIOA_PCOR = PTx13_MASK; while(0)
#define ROW1(x) do if(x) GPIOD_PSOR = PTx2_MASK; else GPIOD_PCOR = PTx2_MASK; while(0)
#define ROW2(x) do if(x) GPIOD_PSOR = PTx4_MASK; else GPIOD_PCOR = PTx4_MASK; while(0)
#define ROW3(x) do if(x) GPIOD_PSOR = PTx6_MASK; else GPIOD_PCOR = PTx6_MASK; while(0)
#define ROW4(x) do if(x) GPIOD_PSOR = PTx7_MASK; else GPIOD_PCOR = PTx7_MASK; while(0)
#define ROW5(x) do if(x) GPIOD_PSOR = PTx5_MASK; else GPIOD_PCOR = PTx5_MASK; while(0)
#define ROW6(x) do if(x) GPIOA_PSOR = PTx12_MASK; else GPIOA_PCOR = PTx12_MASK; while(0)
#define ROW7(x) do if(x) GPIOA_PSOR = PTx4_MASK; else GPIOA_PCOR = PTx4_MASK; while(0)

#define pulse_LAT() do { LAT(1); asm volatile("nop"); LAT(0); LAT(1); } while(0)
#define pulse_SCK() do { SCK(1); SCK(0); } while(0)

extern char _binary_image_raw_start;
rgb_color * uart_image;

void matrix_init() {
    // enable PORT A, B, C, D clocks
    SIM_SCGC5 |= 0x00001E00;

    // set used pins as GPIO
    PORTA_PCR13 = PCR_GPIO_MASK;
    PORTD_PCR2 = PCR_GPIO_MASK;
    PORTD_PCR4 = PCR_GPIO_MASK;
    PORTD_PCR6 = PCR_GPIO_MASK;
    PORTD_PCR7 = PCR_GPIO_MASK;
    PORTD_PCR5 = PCR_GPIO_MASK;
    PORTA_PCR12 = PCR_GPIO_MASK;
    PORTA_PCR4 = PCR_GPIO_MASK;
    PORTB_PCR0 = PCR_GPIO_MASK;
    PORTB_PCR1 = PCR_GPIO_MASK;
    PORTB_PCR2 = PCR_GPIO_MASK;
    PORTC_PCR8 = PCR_GPIO_MASK;
    PORTC_PCR9 = PCR_GPIO_MASK;

    // set used pins as outputs
    GPIOA_PDDR |= PTx13_MASK | PTx12_MASK | PTx4_MASK;
    GPIOB_PDDR |= PTx0_MASK | PTx1_MASK | PTx2_MASK;
    GPIOC_PDDR |= PTx8_MASK | PTx9_MASK;
    GPIOD_PDDR |= PTx2_MASK | PTx4_MASK | PTx6_MASK | PTx7_MASK | PTx5_MASK;

    // reset LED matrix controller and set all output to a valid initialization state
    RST(0);
    SDA(0);
    SCK(0);
    LAT(1);
    SB(1);
    desactivate_rows();

    // wait more than 100ms
    for(int i=0; i<1200000; i++)
        asm volatile("nop");

    // stop reset
    RST(1);
}

void desactivate_rows() {
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}


void activate_row(int row) {
    switch (row) {
    case 0:
        ROW0(1);
        break;
    case 1:
        ROW1(1);
        break;
    case 2:
        ROW2(1);
        break;
    case 3:
        ROW3(1);
        break;
    case 4:
        ROW4(1);
        break;
    case 5:
        ROW5(1);
        break;
    case 6:
        ROW6(1);
        break;
    case 7:
        ROW7(1);
        break;
    }
}

void send_byte(uint8_t val) {
    for(int i=0; i<8; i++) {
        if(val&0x80)
            SDA(1);
        else
            SDA(0);
        pulse_SCK();
        val = val << 1;
    }
}

void mat_set_row(int row, const rgb_color *val) {
    SB(1);
    for(int i=7; i>=0; i--) {
        send_byte(val[i].b);
        send_byte(val[i].g);
        send_byte(val[i].r);
    }

    desactivate_rows();
    for(int i=0; i<50; i++)
        asm volatile("nop");
    pulse_LAT();
    activate_row(row);
}

void init_bank0() {
    SB(0);
    for(int i=0; i<18; i++) {
        send_byte(0xFF);
    }
    pulse_LAT();
}

static void gradient(rgb_color * val, int red, int green, int blue) {
    int gradient;
    for(int i=0; i<8; i++) {
        gradient = (1 + i*2)*(1 + i*2);
        val[i].r = (gradient*red) >> 8;
        val[i].g = (gradient*green) >> 8;
        val[i].b = (gradient*blue) >> 8;
    }
}
void test_pixels() {
    rgb_color grad[8];
    rgb_color grad2[8];
    rgb_color grad3[8];
    gradient(grad, 189, 21, 80);
    gradient(grad2, 233, 127, 2);
    gradient(grad3, 20, 255, 100);

    mat_set_row(0, grad);
    mat_set_row(1, grad2);
    mat_set_row(2, grad3);
    mat_set_row(3, grad);
    mat_set_row(4, grad2);
    mat_set_row(5, grad3);
    mat_set_row(6, grad);
    mat_set_row(7, grad2);
}
static void show_image(rgb_color* image) {
    for(int i=0; i<8; i++) {
        mat_set_row(i, &image[i*8]);
    }
}
void show_image_file() {
    rgb_color* image = (rgb_color *) &_binary_image_raw_start;
    show_image(image);
}

void show_image_uart() {
    show_image((rgb_color *) uart_image);
}
