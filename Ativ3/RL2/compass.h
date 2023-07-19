/* 
 * File:     compass.h 
 * Authors:  Thiago Yukio Nagata Alves
 * Date:     28/04/2016
 * Comments: Controle da b�ssola do rob�
 * Revision history: 
 *           [jo:160608] coment�rios acertados para 2017 e documenta��o Doxygem
 */

#ifndef COMPASS_H
#define COMPASS_H

#include <xc.h>
#include <stdint.h>

void compass_init(); ///< inicializa bussola

uint8_t compass_get_id(); ///< l� identificador da bussola (0x3d)

uint8_t compass_get_status(); ///< l� status da bussola

int16_t compass_get_X(); ///< l� intensidade do campo no eixo x

int16_t compass_get_Y(); ///< l� intensidade do campo no eixo y

int16_t compass_get_Z(); ///< l� intensidade do campo no eixo z

int8_t compass_get_temperature(); ///< l� temperatura

uint16_t compass_get_heading(); ///< le o angulo com o norte

void compass_calibrate(); ///< calibra a bussola, movimenta rob�, requer pwm

void compass_enable(); ///< liga o bussola

void compass_disable(); ///< desliga o bussola

void compass_temperature_enable(); ///< habilita o sensor de temperatura

void compass_temperature_disable(); ///< desabilita o sensor de temperatura

void compass_set_operativemode(uint8_t mode); ///< configura o modo de opera��o
                                              //   0 - low power, 1 - medium, 2 - high, 3 - ultra high

void compass_set_conversionmode(uint8_t mode); ///< configura o modo de convers�o
                                               //   0 - convers�o cont�nua, 1 - convers�o �nica

void compass_set_datarate(uint8_t mode); ///< configura a taxa de dados de sa�da
                                         //   0 - 0.625Hz, 1 - 1.25Hz, 2 - 2.5Hz ..., 7 - 80Hz

void compass_set_fastdatarate(uint8_t mode); ///< habilita taxas de dados mais r�pidas
                                             //   0 - 155Hz,  1 - 300Hz,  2 - 560Hz,  3 - 1000Hz

void compass_set_scale(uint8_t scale); ///< configura o fundo de escala
                                       //   0 - 4 gauss, 1 - 8, 2 - 12, 3 - 16

void compass_reset(); ///< reseta bussola

uint8_t compass_get_interruptsource(); ///< l� fonte de interrup��o (n�o implementado)

void compass_configure_interrupts(uint8_t config); ///< configura interrup��es (n�o implementado))

#endif