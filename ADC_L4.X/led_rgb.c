/* 
 * File:      led_rgb.c
 * Author:    Jun Okamoto Jr.
 * Date:      11/03/2016
 * Comments:  Controla do LED RGB do rob� pela interface SPI
 * Revision history:
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LED_RGB_C
#define	LED_RGB_C

#include <stdint.h>
#include "led_rgb.h"
#include "spi.h"

#define LED_DEVICE_CODE   1 // C�digo do LED RGB no rob�
#define LED_RED_CHANNEL   1
#define LED_BLUE_CHANNEL  2
#define LED_GREEN_CHANNEL 3
///
/// inicializa led_rgb
///
void led_rgb_init() {
  // n�o � necess�rio inicializar nada
  // SPI deve ser inicializado antes de usar o LED RGB
}

///
/// define cor do led, inclusive apagado
///
void led_rgb_set_color(char led_color) {  
  uint8_t command_byte;
  command_byte = (LED_DEVICE_CODE << 5) + (led_color & 0b111); // os 3 bits mais significativos s�o o dispositivo
//  command_byte |= led_color;    // o comando se existir est� nos 5 bits menos significativos
  spi_exchange(command_byte); // traca um byte por SPI  
}

///
/// define a intensidade do canal vermelho
///
void led_rgb_set_red_level(uint8_t level) {
  uint8_t command_byte;
  command_byte = (LED_DEVICE_CODE << 5) + (LED_RED_CHANNEL << 3);
  spi_exchange(command_byte); // envia o comando de defini��o de intensidade
  spi_exchange(level);        // envia o n�vel de intensidade
}

///
/// define a intensidade do canal verde
///
void led_rgb_set_green_level(uint8_t level) {
  uint8_t command_byte;
  command_byte = (LED_DEVICE_CODE << 5) + (LED_GREEN_CHANNEL << 3);
  spi_exchange(command_byte); // envia o comando de defini��o de intensidade
  spi_exchange(level);        // envia o n�vel de intensidade
}

///
/// define a intensidade do canal azul
///
void led_rgb_set_blue_level(uint8_t level) {
  uint8_t command_byte;
  command_byte = (LED_DEVICE_CODE << 5) + (LED_BLUE_CHANNEL << 3);
  spi_exchange(command_byte); // envia o comando de defini��o de intensidade
  spi_exchange(level);        // envia o n�vel de intensidade
}

#endif	/* LED_RGB_C */


