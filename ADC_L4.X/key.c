/* 
 * File:     key.c 
 * Author:   Jun Okamoto Jr.
 * Date:     7/02/2016
 * Comments: Controla leitura de chave
 * Revision history: 
 */

#ifndef KEY_C
#define	KEY_C

#include "always.h"
#include "key.h"

#define KEY RB6           // bit de entrada de chave

// vari�veis globais
volatile bit keyPressed;        // chave pressionada
volatile char debounce;         // contador usado para debounce da chave
volatile char keyStateChanged;  // marca mudan�a de estado da chave de H-L ou L-H

///
/// Inicializa uso da chave por interrup��o-na-mudan�a da porta B.
/// Por enquanto s� para bit 6.
///
void key_init() {
  nRBPU = 0;   // permite usar pull-ups no Port B
  TRISB6 = 1;  // bit 6 da porta B � entrada chave
//  TRISB |= 1 << 6;
  WPUB6 = 1;   // weak pull-up enabled para chave
  IOCB6 = 1;   // interrupt on change enabled
  RBIE = 1;    // habilita interrup��o da Porta B
}

///
/// Retira o bounce da chave dando um tempo controlado pelo par�metro cycles
/// O per�odo de debounce deve ser de 5 a 10 ms.
/// Essa rotina deve ser colcada dentre de uma interru��o peri�dica de algum Timer.
/// Para uma interrup��o peri�dica de 5 ms cycles � 2 o que d� 5 a 10 ms.
/// cycles deve ser alterado de acordo com o per�odo de interrup��o do
/// timer onde a rotina est� inclu�da.
/// @param cycles n�mero de vezes que a interrup��o deve ocorrer para dar 
///               cerca de 10 ms.
///
void key_debounce(int cycles) {
  if (++debounce >= cycles) {  // espera no. de ciclos para dar de 5 a 10 ms
    debounce = 0;              // reseta contador de debounce
    keyStateChanged = FALSE;   // reseta estado de mudan�a da chave
  } // fim - debounce da chave

}

///
/// Faz a leitura da chave.
/// Essa rotina deve ser colocada numa interrup��o-na-mudan�a da porta B.
/// @param port valor lido da porta
///
void key_read(char port) {
  static char key_old = 1;  // valor anterior da chave (1 � o estado inativo)

  // Trata chave
  char key =  (port & 0b01000000) >> 6; // retira o bit 6 que corresponde a chave e coloca com bit menos significativo
  if (key == 0 && key_old == 1) { // detecta borda de subida
    if (!keyStateChanged) { // passou o periodo de debounce e a chave pode ser tratada
      keyPressed = TRUE; // marca como pressionada
      keyStateChanged = TRUE; // marca como mudan�a de estado
      debounce = 0; // reseta debounce
      key_old = key;
    }
  }
  if (key == 1 && key_old == 0) { // detrecta borda de descida
    keyPressed = FALSE; // marca com n�o pressionada
    keyStateChanged = TRUE;  // marca como mudan�a de estado
    debounce = 0; // reseta debounce
    key_old = key;
  }  
}

///
/// Testa se a chave est� pressionada. Se a chave estiver pressionada
/// reseta o seu estado para n�o acionada, com isso detecta s� a borda.
/// Essa rotina deve ser colocada no ponto do programa onde se deseja
/// testar se a chave foi pressionada.
/// @return state TRUE acionada; FALSE n�o acionada
///
char key_pressed() {
  char state = FALSE;       // estado inicial � n�o pressionada
  if (keyPressed == TRUE) { // se a vari�vel global estiver setada
    keyPressed = FALSE;     // reseta o estado da vari�vel
    state = TRUE;           // muda o estado para pressionada
  }
  return state;             // retorna o estado da chave
}
#endif
