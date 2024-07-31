
#ifndef UART_H_
#define UART_H_
#include <stdint.h> // Para uint8_t
#define F_CPU 16000000UL // Frecuencia del reloj del microcontrolador
#define BAUD_PRESCALE(baud) ((F_CPU / (baud * 16UL)) - 1) // Macro para calcular el prescaler del baud rate



volatile char uart_buffer[128]; // Buffer circular para almacenar datos recibidos por UART
volatile uint8_t uart_head; // �ndice de la cabeza del buffer
volatile uint8_t uart_tail; // �ndice de la cola del buffer

/* Inicializa el UART con el baud rate especificado.*/
void UART_init(unsigned int baud);
/* Env�a un solo car�cter a trav�s de UART. */
void UART_send(unsigned char data);
/* Env�a una cadena de caracteres a trav�s de UART. */
void UART_send_string(const char* str);
/* Env�a un n�mero a trav�s de UART. */
void UART_send_number(uint8_t number);
/* Recibe un solo car�cter del buffer UART. */
unsigned char UART_receive(void);
/* Verifica si hay datos disponibles en el buffer UART. */
int UART_available(void);
/* Lee una cadena del buffer UART hasta que se encuentra un delimitador. */
void UART_receive_string(char* buffer, uint8_t max_length);



#endif /* UART_H_ */