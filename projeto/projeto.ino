/* MACRO com frequência do clock utilizado pelo MCU */
#define F_CPU 16000000UL

/* Bibliotecas AVR */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/* Função sprintf */
#include <stdio.h>


/* Funções que vocês utilizarão */

/* String a ser utilizada pela função enviarTexto */
char texto[32];

/* Inicializa AD */
void initAD(void)
{
	/* ADC configuração: Voltagem de Referência = AVCC. */
	ADMUX	|= (1<<REFS0);
	/* Canal de Entrada = ADC0. ADC Habilitado. */ 
	ADCSRA	|= (1<<ADEN);
	/* ADC Prescaler = 128 (125 KHz). */
	ADCSRA	|= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
}

/* Leitura de valor AD */
unsigned int getAD()
{
	/* Inicia Conversão */
	ADCSRA |= 0b01000000;

	/* Espera a Conversão Acabar */
	while ( !(ADCSRA & (1 << ADIF)) ){}
    
	return ADC;
}

/* Inicializa a USART */
void initUSART(void)
{
	/* USART - Character Size - 8, */
	/* Stop Bit - 1, Baud Rate 9600, No Parity */
	UCSR0B |= (1<<RXEN0) | (1 << TXEN0);
	UCSR0C |= (1<<UCSZ01) | (1 << UCSZ00) | (1 << USBS0) ;
	
	/* Baud Rate para f_osc = 16MHz */
	unsigned int ubrr = 59;
	UBRR0H = ( unsigned char ) ( ubrr>>8) ;
	UBRR0L = ( unsigned char ) ubrr ;
}

/* Envia a string "texto" (variável global) via USART */
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

/****************************/


/* Código principal */
int main()
{
  /* Configurações iniciais */
  unsigned int ad;
  
  initAD();
  initUSART();
  
  /* O loop do seu sistema */
  while(1)
  {
    ad = getAD();
    sprintf(texto,"AD: %d\n",(int)ad);
    enviarTexto();
    
    _delay_ms(500);
  }
  
  return 0;
}

