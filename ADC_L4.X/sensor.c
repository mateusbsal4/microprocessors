/* 
 * File:      sensor.c
 * Author:    Jun Okamoto Jr.
 * Date:      11/03/2016
 * Comments:  D� acesso aos sensores e buzzer do rob�
 * Revision history:
 */

#ifndef SENSOR_C
#define SENSOR_C

#include <xc.h> 
#include <stdio.h>
#include "always.h"
#include "delay.h"
#include "adc.h"

#define SENS_PWR RA1

///
/// Liga e desliga alimenta��o dos sensores de buzzer
///
/// @param state 0 - (OFF) desligado, 1 - (ON) ligado
///
void sensor_power(char state) {
  if(state == ON) {  // se comando for para ligar
    SENS_PWR = ON;   // liga o sensor
    delay_ms(50);    // o sensor de proximidade demora ~50 ms para dar uma resposta v�lida
  } else SENS_PWR = OFF; // sen�o desliga o sensor
}
///
/// Inicializa sensores.
/// Configura RA1 para sa�da digital para energia de sensores e buzzer
///           RA0 como canal A/D para sensor de proximidade
///           RA4, RA3, RA2 como digital para sensor de linha
///
void sensor_init() {

  // Alimenta��o dos sensores e buzzer
  ANS1 = 0;            // sensor power � digital
  TRISA1 = 0;          // sensor power � sa�da
  SENS_PWR = OFF;      // alimenta��o dos sensores desligada
  
  // Sensor de linha
  ANSEL &= 0b11100011; // 3 bits de dados digitais RA4, RA3 e RA2
  
  // Sensor de proximidade
  ANS0 = 1;           // canal anal�gico 0
  TRISA0 = 1;         // � entrada
  adc_init(0);        // inicializa conversor A/D para canal 0

}

///
/// Faz a leitura dos 3 bits do sensor de linha
///
int sensorLine_read() {
  
  // tem que manipular diretamente a porta A, bits 2, 3 e 4
  TRISA &= 0b11100011; // primeiro configura como saida
  PORTA |= 0b00011100; // coloca as sa�da em HIGH
  
  delay_us(100);       // espera 100us para carregar capacitor do sensor
  
  TRISA |= 0b00011100; // configura como entrada
  delay_big_us(800);   // espera 800 us antes de ler [jo:160503] atualizado para 800 pois o ch�o do lab � mais escuro
  int line_reading = (PORTA & 0b00011100) >> 2; // l� o valor da porta e reposiciona os bits como menos significativos
   
  return (line_reading); // retorna valor lido do sensor
}

///
/// Faz leitura do sensor de proximidade
///
int sensorNear_read() {
  return (adc_read(0)); // retorna leitura do canal A/D 0
}

#endif
