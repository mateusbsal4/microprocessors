/* 
 * File:     pwm.c 
 * Author:   Jun Okamoto Jr./ Mateus 
 * Date:     7/02/2016 
 * Comments: Gera PWM para acionamento dos motores.
 *           O Timer 1 � utilizado para simular um sinal de PWM com
 *           50% de duty cycle.
 *           Esta implementa��o � s� para testes do hardware, as fun��es
 *           pwm_init e pwm_set dever�o ser implementados na Atividade 6.
 * Revision history:
 * 14/09/2022
 * 13/05/2023 - #defines movidos para c� para poder usar o mesmo .h para simulador e rob�
 */

#ifndef PWM_C
#define PWM_C

#include <stdio.h>
#include "always.h"
#include "pwm.h"

#define DIR1 RA5  // dire��o do PWM 1 [jo:230513] estava no .h
#define DIR2 RA6  // dire��o do PWM 2 [jo:230513] estava no .h

///
/// Inicializa a fun��o de PWM com uma determinada frequencia
///
void pwm_init(){
  
  // Configura��o do Timer 2
  TRISC2 = 1; //desabilita saida CCP1 (pino RC2)
  TRISC1 = 1; //desabilita saida CCP2 (pino RC1)  

  PR2 = 255; //p/freq 19.52kHz ambos canais (max resoluçao)

  //Configuração canal 1
  CCP1CONbits.P1M = 0;    
  CCP1CONbits.CCP1M = 0b1100;
  CCPR1L = 0;      //inicialmente duty cycle 0, motor desligado. CCP1CONbits.DC1B não precisa ser programado (bits em 0 no POR)
  CCP1CONbits.DC1B = 0;                      //devido à resolução de 10 bits duty cicle de 100% corresponderá a n~1000
  //Configuraçãp canal 2
  CCP2CONbits.CCP2M = 0b1100;
  CCPR2L = 0;    //duty cycle inicialmente 0, como explicaddo não se programa CCP2CONbits.DC2B         
  //Configuração timer 2
  TMR2IF = 0; //limpa flag
  T2CONbits.T2CKPS = 0b00; //prescaler de 1  
  TMR2ON = 1; //habilita timer 2

  while(!TMR2IF);   //espera estouro do TMR2
  TRISC2 = 0;   //habilita saídas CCP1 e CCP2
  TRISC1 = 0;

}

///
/// Define o duty cycle da saida PWM
/// @param channel - canal do PWM (1: motor 1; 2: motor 2)
/// @param duty_cycle - porcentagem do duty cycle x 10 (valor de 0 a 1000)
///
void pwm_set(int channel, int duty_cycle){
  if(channel == 1){
    CCPR1L = duty_cycle >> 2;  //8 bits mais significativos do duty_cycle 
  }
  else if(channel == 2){
    CCPR2L = duty_cycle >> 2;  //8 bits mais significativos do duty_cycle   
  }
}

///
/// Altera a dire��o de movimento
/// @param dir - c�digo de dire��o
///              0 - para frente (ou qualquer outro valor)
///              1 - para tr�s
///              2 - gira para a esquerda
///              3 - gira para a direira
///

void pwm_direction(int dir) {
  switch (dir) {
    case 1: // para tr�s
      DIR1 = 1;
      DIR2 = 1;
      break;
    case 2: // para a esquerda
      DIR1 = 1;
      DIR2 = 0;
      break;
    case 3: // para a direita
      DIR1 = 0;
      DIR2 = 1;
      break;
    default: // para frente
      DIR1 = 0;
      DIR2 = 0;
  } 
}


#endif
