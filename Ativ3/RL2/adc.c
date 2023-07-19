/* 
 * File:     adc.c
 * Author:   Jun Okamoto Jr.
 * Date:     27/02/2016
 * Comments: Configura e faz leitura de canais anal�gicos
 * Revision history: 
 */

#ifndef ADC_C
#define ADC_C

#include "adc.h"
#include "always.h" // para usar defini��es de INPUT e OUTPUT e union

///
/// Inicializa um canal anal�gico
///
/// @param adc_channel n�mero do canal (0-4, 8-13 para PIC16F886)
///
void adc_init (unsigned char adc_channel) {

  switch (adc_channel) { // configura entrada e canal anal�gico
    case 0: // AN0
      TRISA0 = INPUT; // entrada
      ANS0 = ANALOG;  // canal anal�gico
      break;
    case 1: // AN1
      TRISA1 = INPUT; // entrada
      ANS1 = ANALOG;  // canal anal�gico
      break;
    case 2: // AN2
      TRISA2 = INPUT; // entrada
      ANS2 = ANALOG;  // canal anal�gico
      break;
    case 3: // AN3
      TRISA3 = INPUT; // entrada
      ANS3 = ANALOG;  // canal anal�gico
      break;
    case 4: // AN4
      TRISA5 = INPUT; // entrada
      ANS4 = ANALOG;  // canal anal�gico
      break;
    case 8: // AN8
      TRISB2 = INPUT; // entrada
      ANS8 = ANALOG;  // canal anal�gico
      break;
    case 9: // AN9
      TRISB2 = INPUT; // entrada
      ANS9 = ANALOG;  // canal anal�gico
      break;
    case 10: // AN10
      TRISB1 = INPUT; // entrada
      ANS10 = ANALOG; // canal anal�gico
      break;
    case 11: // AN11
      TRISB4 = INPUT; // entrada
      ANS11 = ANALOG; // canal anal�gico
      break;
    case 12: // AN12
      TRISB0 = INPUT; // entrada
      ANS12 = ANALOG; // canal anal�gico
      break;
    case 13: // AN13
      TRISB5 = INPUT; // entrada
      ANS13 = ANALOG; // canal anal�gico
      break;
    default:  // sen�o for canal anal�gico v�lido 
      return; // sai
  }
  ADCON0bits.ADCS = 2;  // clock de convers�o FOSC/32 em 20MHz d� 1.6us
  // configura tens�o de refer�ncia
  ADCON0bits.CHS = adc_channel; // canal anal�gico de 0 a 13 
  ADCON1bits.ADFM = 1;          // justificado � direita
  ADON = 0; // desabilita canal anal�gico para n�o consumir energia
  ADIE = 0; // desabilita interrup��o, n�o � usada nessa biblioteca
} 

///
/// Faz a leitura de um canal ADC e retorna o valor de 10-bits
/// numa vari�vel inteira
///
/// @param adc_channel n�mero do canal (0-4, 8-13 para PIC16F886)
///
unsigned int adc_read(unsigned char adc_channel) {
	
  union wordtype adc_result; // resultado da convers�o

  // Para PIC16F886 s�o v�lidos canais 0-4 e 8-13, fora disso sai 
  if ((adc_channel > 4 && adc_channel < 8) || adc_channel > 13) return (0);
 
  // continua processo  
  ADCON0bits.CHS = adc_channel; // seleciona canal do ADC
  ADON = 1;    // liga canal anal�gico
  ADIF = 0;    // reseta flag de final de convers�o
  ADRESL = 0;  // limpa registrador de resultado da convers�o (LSB)
  ADRESH = 0;  // limpa registrador de resultado da convers�o (MSB)				 

  GO = 1;                         // dispara processo de convers�o  
  while(!ADIF) continue;          // espera convers�o terminar
  adc_result.byte.low = ADRESL;   // LSB do resultado da convers�o
  adc_result.byte.high = ADRESH;  // MSB do resultado da convers�o
  ADON = 0;                       // desliga canal anal�gico
  return (adc_result.word);       // retorna valor da convers�o
}

#endif
