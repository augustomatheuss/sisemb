#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

/* Onde estão as funções que vocês utilizarão */
#include "caminho-completo/sisemb.h"

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
    sprintf(buffer,"AD: %d\n",ad);
    enviarTexto();
  }
  
  return 0;
}
