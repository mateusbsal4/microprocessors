/* 
 * File:     pwm.h 
 * Author:   Jun Okamoto Jr.
 * Date:     7/02/2016
 * Comments: Gera PWM para acionamento dos motores
 * Revision history: 
 * 13/05/2023 - #defines movidos para pwm.c para poder usar no simulador e no rob�
 */

#ifndef PWM_H
#define PWM_H

#include <xc.h>

//#define DIR1 RA5  // dire��o do PWM 1
//#define DIR2 RA6  // dire��o do PWM 2

void pwm_init(); ///< inicializa a funcao de PWM com uma determinada frequencia

void pwm_set(int channel, int duty_cycle); ///< define o duty cycle para cada motor

void pwm_direction(int dir); ///< altera a dire��o do movimento


#endif