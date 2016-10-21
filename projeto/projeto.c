/* MACRO com frequência do clock utilizado pelo MCU */
#define F_CPU 16000000UL

/* Bibliotecas AVR */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/* Função sprintf */
#include <stdio.h>


/* Funções que vocês utilizarão */
/* Você pode revisar a descrição dos comandos junto ao datasheet */

/* String a ser utilizada pela função enviarTexto */
char texto[64];

/* Inicializa AD */
void initAD(void)
{
	/* ADC configuração: Voltagem de Referência = AVCC. */
	ADMUX |= (1<<REFS0);
	/* Canal de Entrada = ADC0. ADC Habilitado. */ 
	ADCSRA  |= (1<<ADEN);
	/* ADC Prescaler = 128 (125 KHz). */
	ADCSRA  |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
}

/* Leitura de valor AD na porta ADC0 */
/* A port ADC0 é a PC0 no MCU e analog in 0 no Arduino Uno */
unsigned int getAD()
{
	/* Inicia Conversão */
	ADCSRA |= 0b01000000;

	/* Espera a Conversão Acabar */
	while ( !(ADCSRA & (1 << ADIF)) ){}
   
	/* ADC une os valores dos registradores ADCH e ADCL */
	/* Guarda o valor da conversão AD */
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
	unsigned int ubrr = 207; /* 103 */
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

/* Inicializa PWM - Utilizando Contador 0, porta OC0A */
/* A porta OC0A é a PD6 no MCU e porta 6 no Arduino Uno */
void initPWM(void)
{
	/* Fast PWM - zera na comparação com OC0A */
	TCCR0A |=  (1<<COM0A1);
	/* Fast PWM - TOP = 0xFF, Atualização = OCR0A, Overflow em TOP */
	TCCR0A |= (1<<WGM00)| (1<<WGM01);
	/* Prescale = clock_IO / 1 */
	TCCR0B |= (1<<CS00);
    /* Direção de saída para a porta PD6 */
    DDRD |= 0b01000000;
}

/* Confere um valor de 0 a 100 (%) para o PWM */
void setPWM(unsigned char level)
{
	OCR0A = ((unsigned char) ((((float)level)/100.0)*255.0));
}

/* Inicializa PWM 2 - Utilizando Contador 0, porta OC0A */
/* A porta OC2A é a PB3 no MCU e porta 11 no Arduino Uno */
void initPWM2(void)
{
	/* Fast PWM - zera na comparação com OC0A */
	TCCR2A |=  (1<<COM2A1);
	/* Fast PWM - TOP = 0xFF, Atualização = OCR0A, Overflow em TOP */
	TCCR2A |= (1<<WGM00)| (1<<WGM01);
	/* Prescale = clock_IO / 1 */
	TCCR2B |= (1<<CS00);
    /* Direção de saída para a porta PD6 */
    DDRB |= 0b00001000;
}

/* Confere um valor de 0 a 100 (%) para o PWM */
void setPWM2(unsigned char level)
{
	OCR2A = ((unsigned char) ((((float)level)/100.0)*255.0));
}
/****************************/


/* Código principal */
int main()
{
	/* Configurações iniciais */
	unsigned int ad;
  
	initAD();
	initUSART();
  
	/* Mensagem inicial */
	sprintf(texto,"Primeira parte do nosso projeto!\n\n");
	enviarTexto();
	_delay_ms(3000);

	/* O loop do seu sistema */
	while(1)
	{
		ad = getAD();
		sprintf(texto,"AD: %d\n", (int)ad);
		enviarTexto();
		
		/* Espera 500 ms */
		_delay_ms(500);
	}
  
	return 0;
}

