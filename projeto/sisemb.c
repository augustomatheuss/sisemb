#include "sisemb.h"

void initAD(void)
{
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
}

unsigned int getAD()
{
	/* Inicia Conversão */
	ADCSRA |= 0b01000000;

	/* Espera a Conversão Acabar */
	while ( !(ADCSRA & (1 << ADIF)) ){}
    
	return ADC;
}

void initUSART(void)
{
	/* USART - Character Size - 8, */
	/* Stop Bit - 1, Baud Rate 9600, No Parity */
	UCSR0B |= ( 1 << RXEN0) | ( 1 << TXEN0);
	UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 ) | ( 1 << USBS0) ;
	
	/* Baud Rate para f_osc = 16MHz */
	unsigned int ubrr = 103;
	UBRR0H = ( unsigned char ) ( ubrr>>8) ;
	UBRR0L = ( unsigned char ) ubrr ;
}

unsigned char enviarTexto()
{
	unsigned char c = 0;
	while( texto[c] != '\0' )
	{
	while (!( UCSR0A & (1<<UDRE0) )) ;
	UDR0 = texto[c];
	c++;
	}
}

