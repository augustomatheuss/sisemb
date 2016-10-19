#ifndef SISEMB_H
#define	SISEMB_H

/* ADC configuração: Voltagem de Referência = AVCC. */
/* Canal de Entrada = ADC0. ADC Habilitado. */ 
/* ADC Prescaler = 128 (125 KHz). */
void initAD(void);

/* Get AD Value */
unsigned int getAD(void);

void initSerial(void);

/* String buffer */
char texto[32];

/* Configura USART */
void initUSART(void);

/* Enviar a string texto via USART */
unsigned char enviarTexto(void);

#endif

