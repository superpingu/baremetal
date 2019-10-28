#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

/* a pixel with RGB color */
typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} rgb_color;

/* contains an image sent via the serial port */
extern rgb_color * uart_image;

/* initialize 8*8 LED matrix */
void matrix_init();

/* desactivate all the matrix rows */
void desactivate_rows();

/* activate the given matrix row */
void activate_row(int row);

/* send a byte to the LED matrix */
void send_byte(uint8_t val);

/* set a row of the matrix */
void mat_set_row(int row, const rgb_color *val);

/* init BANK0 to maxiumum value */
void init_bank0();

/* test LED matrix by displaying gradients of red, green and blue */
void test_pixels();

/* display the image in image.raw */
void show_image_file();

/* display the image sent via serial port*/
void show_image_uart();

#endif
