#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include "ADC/ADC.h"
#include "SPI_SLAVE/SPI_SLAVE.h"
#include <avr/interrupt.h>

volatile uint8_t current_channel = 1;
volatile uint8_t adc_value1, adc_value2;

ISR(ADC_vect) {
	if (current_channel == 1) {
		adc_value1 = ADC;
		current_channel = 2;
		ADC2();
		} else {
		adc_value2 = ADC;
		current_channel = 1;
		ADC1();
	}
	habilitar_conversion();
}

int main(void) {
	SpiInit(SPI_SLAVE_SS, SPI_DATA_ORDER_MSB, SPI_CLOCK_IDLE_LOW, SPI_CLOK_FIRST_EDGE);
	ADC_init(128);
	habilitar_conversion();
	ADC1();
	SPCR |= (1 << SPIE);
	sei();

	while (1) {
		uint8_t SpiValor = SPDR;
		if (SpiValor == 'c') {
			SpiWrite(adc_value1);
			_delay_ms(1);
			} else if (SpiValor == 'd') {
			SpiWrite(adc_value2);
			_delay_ms(1);
		}
	}
}
