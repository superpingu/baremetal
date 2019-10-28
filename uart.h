#ifndef UART_H
#define UART_H

/* initialize the UART at 115200 baud, 1 stop bit, no parity */
void uart_init();

/* send a char on the UART0 */
void uart_putchar(char c);

/* receive a char from the UART (blocks until a char is received) */
unsigned char uart_getchar();

/* send a string through UART0 and appends a newline character*/
void uart_puts(const char *s);

/* receive characters from the UART until size-1 characters has been received
 * or a newline character is received */
void uart_gets(char *s, int size);

#endif
