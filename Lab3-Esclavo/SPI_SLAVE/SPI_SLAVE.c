#include "SPI_SLAVE.h"
void SpiInit(Spi_Type Type,Spi_Data_Order DataOrder,Spi_Clock_Polarity ClockPolarity,Spi_Clock_Phase ClockPhase){
/* PB2 = SS
   PB3 = MOSI
   PB4 = MISO
   PB5 = SCK   
	*/
	if(Type & (1<<MSTR)) //master mode
	{
		DDRB |= (1<<DDB3)|(1<<DDB5)|(1<<DDB2);//  MOSI, SCK, SS
		DDRB &= ~(1<<DDB4);//MISO
		SPCR |= (1<<MSTR); //MASTER
		uint8_t temp = Type & 0b00000111;
		switch(temp){
			
  			case 0://div2
				SPCR &= ~((1<<SPR1)|(1<<SPR0));
				SPSR |= (1<<SPI2X);
			break;
			
			case 1://div4
				SPCR &= ~((1<<SPR1)|(1<<SPR0));
				SPSR &= ~(1<<SPI2X);
			break;
			
			case 2://div8
				SPCR |= (1<<SPR0);
				SPCR &= ~(1<<SPR1);
				SPSR |= (1<<SPI2X);
			break;
			
			case 3://div16
				SPCR |= (1<<SPR0);
				SPCR &= ~(1<<SPR1);
				SPSR &= ~(1<<SPI2X);
			break;
			
			case 4://div32
				SPCR &= ~(1<<SPR0);
				SPCR |= (1<<SPR1);
				SPSR |= (1<<SPI2X);
			break;
			
			case 5://div64
				SPCR &= ~(1<<SPR0);
				SPCR |= (1<<SPR1);
				SPSR &= ~(1<<SPI2X);
			break;
			
			case 6://div128
				SPCR |= ((1<<SPR1)|(1<<SPR0));
				SPSR &= ~(1<<SPI2X);
			break;
		}
		
	} else{ //si es esclavo
		DDRB |=(1<<DDB4);//miso
		DDRB &= ~((1<<DDB3)|(1<<DDB5)|(1<<DDB2));//mosi, sck, ss
		SPCR &= ~(1<<MSTR);//SALVE
		
	}
	//ENABLE, DATA ORDER, CLOCK POLARITY, CLOCK PHASE
	SPCR |= (1<<SPE)|DataOrder|ClockPolarity|ClockPhase;
	
}

void  SpiWrite(uint8_t dat){//WRITE DATA TO SPI
	SPDR = dat;
}
unsigned SpiDataReady(){// check wether data is ready to read
	if(SPSR & (1<<SPIF))
	return 1;
	else
	return 0;
	
}

uint8_t SpiRead(void){//lee el dato recivido
	while(!(SPSR & (1<<SPIF))); // ESPERAR HASTA QUE LA VARIABLE 
	return(SPDR);
}