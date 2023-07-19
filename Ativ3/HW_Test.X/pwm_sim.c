/* 
 * File:     pwm_sim.c 
 * Author:   Jun Okamoto Jr.
 * Date:     7/02/2016 
 * Comments: Gera PWM para acionamento dos motores.
 *           O Timer 1 � utilizado para simular um sinal de PWM com
 *           50% de duty cycle.
 *           Esta implementa��o � s� para testes do hardware, as fun��es
 *           pwm_init e pwm_set dever�o ser implementados na Atividade 6.
 * Revision history:
 * 14/09/2022
 * 12/05/2023 - pwm.c adaptado para simulador
 * 13/05/2023 - #defines movidos para c� para poder usar .h no simulador e no rob�
 */

#ifndef PWM_C
#define PWM_C

#include <stdio.h>
#include "always.h"
#include "pwm.h" // [jo:230513] usa o mesmo .h do rob�

#define PWM1 RC2  // somente para teste de hw [jo:230513] estava comentado
#define PWM2 RC1  // somente para teste de hw [jo:230513] estava comentado
#define DIR1 RB1  // dire��o do PWM 1 [jo:230513] movido do .h para c�
#define DIR2 RB2  // dire��o do PWM 2 [jo:230513] movido do .h para c�

///
/// Inicializa a fun��o de PWM com uma determinada frequencia
///
void pwm_init(){
  // Para os testes � usado o Timer 1 e as sa�das dos sinais de PWM para 
  // os motores s�o configuradas diretamente nos pinos.
  // Dever� ser re-implementada utilizando os PWM's com sa�das como CCP1 e CCP2
  // naAtividade 6
  
  // Configura��o do Timer 1
  TMR1ON = 1;   // habilita Timer 1
  TMR1CS = 0;   // usa clock interno FOSC/4
  T1OSCEN = 0;  // oscilador LP desligado
  T1CKPS0 = 0;  // prescaler 1:1
  T1CKPS1 = 0;  // prescaler 1:1
  TMR1GE = 0;   // Timer 1 est� sempre contando
  TMR1 = 0xffff - 1000; // contagem
  TMR1IE = 0; // inicialmente interrup��o est� desligada para Timer 1
  PEIE = 1;   // habilita interrup��es de perif�ricos para poder usar Timer 1
  
  // Sa�da dos sinais de PWM
  TRISC1 = 0; // RC1 � sa�da para PWM2
  TRISC2 = 0; // RC2 � sa�da para PWM1
  PWM1 = 0;   // sa�da do PWM1 � zero inicialmente
  PWM2 = 0;   // sa�da do PWM2 � zero inicialmente
  
  // Sa�da dos sinais de dire��o
  // PWM1_DIR (RB1) [jo:230512] sinais alterados para simulador
  ANS10 = 0;  // RB1 � digital
  TRISB1 = 0; // RB1 � sa�da
  DIR1 = 0;   // dire��o do motor 1 (RB1)
  // PWM2_DIR (RB2) [jo:230512] sinais alterados para imulador
  ANS8 = 0;   // RB2 � digital
  TRISB2 = 0; // RB2 � sa�da
  DIR2 = 0;   // dire��o do motor 2 (RB2)
}

///
/// Define o duty cycle da saida PWM
/// @param channel - canal do PWM (1: motor 1; 2: motor 2)
/// @param duty_cycle - porcentagem do duty cycle x 10 (valor de 0 a 1000)
///
void pwm_set(int channel, int duty_cycle){
  // N�o implementado para os testes  
  // dever� ser implementado pelos alunos na Atividade 6
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

// Fun��es somente para teste de hardware, n�o devem ser implementadas na Atividade 6

// Desliga os motores
void pwm_off(void) {
  TMR1IE = 0; // desliga Timer 1 que para o sinal nas sa�das PWM
  PWM1 = 0;   // para motor 1
  PWM2 = 0;   // para motor 2
}

// Liga os motores com duty cycle fixo determinado pelo Timer 1
void pwm_on(void) {
  TMR1IE = 1; // ligando a interrup��o do Timer 1 produz sinal com 50% de duty cycle nas duas sa�das para os motores
}

// Controle das sa�das de PWM para interrup��o do Timer 1
void pwm_output_control(void) {
  PWM1 = ~PWM1;  // inverte a sa�da do PWM1
  PWM2 = ~PWM2;  // inverte a sa�da do PWM2
  TMR1 = 0xffff - 1000; // recarrega a constante do Timer 1
  TMR1IF = 0;  // limpa o flag de interrup��o  
} 

#endif
