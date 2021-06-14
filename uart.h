
#ifndef UART_H
#define UART_H



#define XON 0x11
#define XOFF 0x13

/**********************************************************

             functions proto-types

*****************************************************/

void uart_init(unsigned int baudrate);


void uart_send_char(const char c);


void uart_send_string(const char * const string );





#endif