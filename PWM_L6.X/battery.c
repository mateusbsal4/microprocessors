/* 
 * File:   battery.c
 * Author:   Jun Okamoto Jr.
 * Date:     9/02/2016
 * Comments: Faz leitura no n�vel da bateria do rob�
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BATTERY_C
#define	BATTERY_C

#include "battery.h"
#include "spi.h"

///
/// Inicializa leitura de n�vel de bateria.
///
void battery_init() {
  // Supondo que o SPI j� foi incializado, n�o h� nada para fazer,
  // � s� ler o n�vel da bateira direto, sen�o o SPI deve ser incializado aqui.
  // TODO: achar um jeito de saber se o SPI est� inicializado e se n�o estiver, inicializar SPI
//  spi_init(); 
}

///
/// Faz a leitura do n�vel da bateria
/// @return: n�vel da bateria
///
uint8_t battery_level() {
  uint8_t level;       // n�vel a bateria
  spi_write(0x80);  // envia comando para leitura do n�vel de bateria pelo SPI
  level = spi_read();  // envia 0x00 para ler um byte e recebe n�vel
  return level; // retorna o n�vel da bateria
}

#endif
