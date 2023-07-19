// PMR3406 - Microprocessadores em Automa��o e Rob�tica
//
// Programa para testes iniciais do hardware.
//
// Esse programa testa os seguintes itens:
//   interrup��o pelo Timer 0
//   porta de sa�da para LED
//   canal serial RS232
//   comunica��o com display de LCD do rob�
//   comunica��o com LED RGB do rob�
//   som do rob�
//   leitura de nivel de bateria
//   leitura de sensor de proximidade com convers�o A/D
//   leitura de sensor de linha
//   pinos de sa�da dos PWMs com 50% de duty cycle por Timer 1
//
// Autor: Jun Okamoto Jr.
// Data: 12/02/2016
// Updated: 10/05/2023 v2.1 - atualiza��o para sintaxe do XC8 v2.40 e outros
//          12/05/2023 v2.2 - alterada estrutura do loop principal
//          16/05/2023 v2.3 - ajustes para rodar no simulador e rob�
//
// ATEN��O: antes de copiar qualquer parte desse c�digo para uso pr�prio,
// o aluno deve entender o que o c�digo faz. Caso o aluno seja questionado
// oralmente e n�o saiba responder, sua avalia��o ser� prejudicada.
// Adicionalmente, dever�o ser retiradas as parte n�o necess�rias para 
// a atividade em quest�o.
//

// ------------------- PARA USO NO SIMULADOR -------------------
// Descomentar a linha abaixo se for usar no simulador,
// comentar se for usar no rob� real e substituir os arquivos
// lcd8x2_sim.c e pwm_sim.c usados no simulador por
// lcd8x2.c e pwm.c usados no rob� clicando com o bot�o da 
// direita sobre o nome do arquivo e selecionar "Include file(s)
// in current configuration" ou "Exclude file(s) from current configuration"
//#define SIMULATOR // descomentar esta linha para simulador, comentar para rob�
// FIM---------------- PARA USO NO SIMULADOR -------------------

// Gerado automaticamento por "Window > PIC Memory Views > Configuration Bits"
// <-- A partir daqui -->
#include <xc.h>

// #pragma config statements should precede project file includes.

// CONFIG1
#pragma config FOSC = EC        // Oscillator Selection bits (EC: I/O function on RA6/OSC2/CLKOUT pin, CLKIN on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN =OFF       // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// <--------------- At� aqui -->

// Includes do projeto
// <------------ incluir sempre <- daqui ->
#include <stdio.h>    // para poder usar sprintf()
#include "always.h"   // estruturas e unions �teis (incluir sempre)
#include "delay.h"    // diversos atrasos (incluir sempre)
// <------------ incluir sempre <- at� aqui ->
// <------------ incluir se for usar <- daqui ->
#ifndef SIMULATOR
#include "spi.h"      // interface SPI, no rob� necess�rio para LCD e outros
#include "battery.h"  // medi��o de n�vel de bateria do rob�
#include "led_rgb.h"  // LED RGB do rob�
#include "compass.h"  // bussola do rob�
#endif
#include "pwm.h"      // PWM para testes, os alunos devem alterar para a Atividade 6
#include "lcd8x2.h"   // para usar o LCD, no rob� � necess�rio o SPI
#include "serial.h"   // para utilizar canal de comunica��o serial
#include "key.h"      // para utilizar chave da placa
#include "sensor.h"   // sensores de linha, de proximidade e buzzer
// <------------ incluir ser for usar <- at� aqui ->

// Defini��es
#define VERSION "2.3"

// Sa�das
#define LED RB5      // bit de sa�da para o LED
#define BUZZER RB7   // bit para buzzer

// Macros
#define testbit(var, bit) ((var) & (1 << (bit)))
#define setbit(var, bit) ((var) |= (1 << (bit)))
#define clrbit(var, bit) ((var) &= ~(1 << (bit)))

// Vari�veis globais v�o aqui se existirem
// todas as vari�veis globais usadas em interrup��o precisam ser "volatile"
// � necess�rio colocar a descri��o de cada vari�vel

// Fun��o de tratamen to de interru��es
// Aten��o: essta fun��o n�o deve ser chamada em nenhum lugar do seu programa.
// Ela � chamada somente na ocorrencia de uma interrup��o.
// No caso deste programa, o Timer 0 � programado para gerar um pedido de
// interrup��o a cada ~5 ms.
  void __interrupt() isr(void) {  // Fun��o geral de tratamento de interrup��o
    
    // vari�veis locais declaradas static mant�m o valor
    static int tick = 0;     // contador de vezes que o Timer 0 interrompe
    
    // Timer 0
    // Interrompe a cada 5 ms aproximadamente.
    // Faz pisca o LED a cada 1 seg aproximadamente.
    // Controla o tempo de debounce da chave em conjunto com o I-O-C do PORT B
    if (TMR0IE && TMR0IF) {    // se for interrup��o do Timer 0
      
      // inverte o LED a cada segundo
      if (++tick >= 200) { // se interromper 200x � ~1 s
        tick = 0;          // ent�o zera o contador
        LED = ~LED;        // inverte LED      
      } // fim - contagem de vezes que ocorre interrup��o
          
      // Debounce da chave. Deve ser inclu�do na interrup��p peri�dica de Timer.
      // S�o 2 ciclos para debounce entre 5 e 10 ms para interrup��o de ~5ms. 
      // Deve ser alterado de acordo com o tempo dado pela interrup��o do Timer.
      // Por exemplo, se a interrup��o for a cada 1 ms, o par�metro deve ser 10
      // o que resulta num debounce de 9 a 10 ms.
      key_debounce(2); // 2 � o n�mero de ciclos para dar 5 a 10 ms
      
      TMR0 = 0xff - 98;   // recarrega contagem no Timer 0 p/ 5,0176ms
      TMR0IF = 0;         // limpa interrup��o
    } // fim - tratamento do Timer 0
    
    // Interrupt-on-change do PORT B usado pela chave
    // O tempo de debounce � controlado pelo Timer 0. A mudan�a de estado da chave
    // dispara uma contagem de tempo pelo Timer 0 de 5 a 10 ms. Toda a vez que 
    // houver mudan�a de estado da chave a contagem de tempo de debounce � 
    // zerada.
    if (RBIE && RBIF) { // se for mudan�a estado do Port B
      char portB = PORTB; // faz a leitura do Port B, isso reseta a condi��o de interrup��o junto com RBIF = 0
      key_read(portB);    // faz a leitura da chave
      RBIF = 0;           // reseta o flag de interrup��o para poder receber outra interrup��o
    } // fim - tratamento I-O-C PORT B
    
    // Timer 1
    // Simula o PWM para testes de hardware na Atividade 3.
    // Na Atividade 6 os alunos dever�o escrever as 
    // pr�prias rotinas de PWM e n�o dever� ser utilizado o Timer 1 para tanto.
    if (TMR1IE && TMR1IF) {  // se for interrup��o de Timer 1
      pwm_output_control();  // controla as sa�das PWM e reseta Timer 1
    } // fim - Interrupc�o do Timer 1
    
    // Outras interrup��es aqui
    
} // fim - Tratamento de todas as interru��es

// inicializa Timer 0
void t0_init(void) {
  // o Timer 0 � utilizado para interrup��o peri�dica a cada 5 ms aproximadamente
  OPTION_REGbits.T0CS = 0; // usa clock interno FOSC/4
  OPTION_REGbits.PSA = 0;  // Prescaler � para Timer 0 e n�o para WDT
  OPTION_REGbits.PS = 7;   // ajusta Prescaler para 1:256
  TMR0 = 0xff - 98;        // valor inicial do Timer 0 p/ 5,0176 ms
  TMR0IE = 1;              // habilita interrup��o do Timer 0
}

// inicializa LED
void led_init(void) {
  TRISB5 = 0;  // RB5 � sa�da para LED
  ANS13 = 0;   // RB5/AN13 � digital  
  LED = 0;
}

// inicializa Buzzer
void buzzer_init(void) {
 TRISB7 = 0;  // RB7 � sa�da para BUZZER 
 BUZZER = 0; 
}

// Toca um beep
// Para usar o BUZZER o SENSOR POWER deve estar ligado.
void beep() {
  BUZZER = ON;        // liga buzzer
  delay_big_ms(200);  // por 0,2s
  BUZZER = OFF;       // desliga buzzer
}

// Mostra mensagem inicial no LCD
void welcome_message() {
  char sVar[9];          // string de 8 caracateres
  lcd_goto(0);           // vai para in�cio da 1a. linha
  lcd_puts("Teste Hw");  // mostra string no LCD para saber que est� funcionando
  delay_ms(1);           // d� um tempo para o display mostrar a mensagem       
  sprintf(sVar, "v%s    ", VERSION); // armazena vers�o em forma de texto
  lcd_goto(64);          // vai para o in�cio da 2a. linha
  lcd_puts(sVar);        // coloca no. da vers�o  
}

// mostra o n�mero do teste no LED RGB, LCD e serial
void display_test_number(int testNumber) {
  char sVar[9];
  
#ifndef SIMULATOR
  // mostra no LED RGB
  led_rgb_set_color(testNumber); // coloca cor correspondente � contagem
#endif
  
  // mostra no LCD 
  if (testNumber == 0) {  // se for final de testes
    delay_ms(1);          // precisa de uma espera para n�o embaralhar o lcd
    lcd_goto(64);         // vai para linha 2, coluna 1 do LCD
    lcd_puts("       ");  // limpa 7 chars, n�o d� para escrever mais seguido (testado)
    lcd_goto(71);         // vai at� o 8o. char
    lcd_putchar(' ');     // limpa char
    sprintf(sVar, "end"); // escreve fim
  } else                  // se for continuar sequ�ncia de testes
    sprintf(sVar, "%d       ", testNumber); // gera string para display
  lcd_goto(0); // coloca o cursor na 6a. posi��o da linha de cima do LCD
  lcd_puts(sVar); // mostra contagem no LCD
  
  // mostra no serial
  if (testNumber == 0) { // se for fim de testes
    delay_ms(1);    //precisa esperar um pouco
    putst("end\r"); // mostra mensagem de t�rmino de testes
  } else {          // se for continuar sequ�ncia de testes
    putch(testNumber + '0');  // envia o valor pelo serial + '0' corrige valor para ASCII
    putch('-');               // coloca um hifem para separar valores
  }

}

/// Programa Principal
void main (void) {
  
  // vari�veis locais
  char sVar[9];                 // string auxiliar para 8 caracteres
  int currentTest = 0;          // n�mero do teste atual entre 1 e 7, 0 significa nenhum teste rodando
  int nearSensorData;           // valor do sensor de proximidade
  union chartype lineSensor;    // valor do sensor de linha
  char serialIn = 255;          // caracter recebido pelo canal serial
  char keyIn = FALSE;           // tecla pressionada, TRUE = sim
  char onlyOnce = 0;  // controla se o teste roda s� uma vez no loop principal
  
  //
  // Inicializa��es 
  //
  
  // Inicializa o rob�
#ifndef SIMULATOR
  spi_init();      // inicializa spi para lcd, led_rgb, battery, compass - deve ser comentado para uso no simulador
  led_rgb_init();  // inicializa LED RGB - deve ser comentado para uso no simulador
  battery_init();  // inicializa leitura de bateria - deve ser comentado para uso no simulador
  compass_init();  // inicializa b�ssola - deve ser comentado para uso no simulador
#endif
  lcd_init();      // inicializa lcd
  sensor_init();   // inicializa sensores

  // Inicializa��es da placa local
  t0_init();      // inicializa Timer 0 para interrup��o peri�dica de ~5 ms
  serial_init();  // inicializa canal de comunica��o serial
  pwm_init();     // inicializa PWM
  key_init();     // inicializa chave
  led_init();     // inicializa LED para debug
  buzzer_init();  // inicializa buzzer
  
  // Controle de interrup��es
  GIE = 1;    // habilita interrup��es

  //
  // Configura��es iniciais
  //
   
  // Sensores [jo:230512] no simulador n�o precisa ligar energia para os sensores 
  //                      e o buzzer funciona independente
#ifndef SIMULATOR
  sensor_power(ON);      // liga energia dos sensores, demora 40 ms para ligar o sensor de proximidade
#endif

  // LCD
  delay_s(2); // espera para poder ler mensagem de reset
  lcd_clear();      // limpa LCD, n�o deve ser usado dentro de loops pois demora muito
  lcd_show_cursor(OFF);  // desliga cursor do LCD 

  // mensagem inicial no LCD 
  welcome_message(); // coloca mensagem inicial no LCD 
  beep();            // toca beep para sinalizar que est� pronto
  
  //
  // Loop principal - nunca deve parar esperando um evento, sempre pode ser interrompido
  //
  while (1) {  // para sempre
    
    keyIn = key_pressed(); // armazena status da chave
    serialIn = chkchr();   // captura buffer do canal serial
    
    // Trata chave pressionada
    if (keyIn) { // se detectar que a chave foi pressionada 
      currentTest++; // incrementa n�mero do teste      
      if (currentTest == 8) {
       currentTest = 0; // fim dos testes
       onlyOnce = 0;    // libera todos os testes para executar
      }
      display_test_number(currentTest); // apresenta o n�mero do teste
      beep(); // toca um beep
      LED = 1;
    }
    
    // Trata caracter recebido pelo serial
    if (serialIn >= '1' && serialIn <= '7') { // s� aceita testes de 1 a 7
      currentTest = serialIn - '0'; // o valor recebido corresponde ao n�mero do teste 
      display_test_number(currentTest); // apresenta o n�mero do teste
      beep(); // toca um beep
    }
                    
    // Faz testes de 1 a 7
    // 1 a 4 executam a cada passada pelo loop
    // 5 a 7 executam s� uma vez para cada passada pelo loop
    // a vari�vel onlyOnce controla se a cada passada pelo loop
    // s� uma vez por passada no loop, 1 bit para cada teste
    switch (currentTest) { // vai para o n�mero do teste

      case 1: // bateria
        onlyOnce = 0;   // executa a cada loop
        pwm_off();      // desliga motores
#ifdef SIMULATOR
        sprintf(sVar, "Bat: %d", 255); // monta string com valor - para teste no simulador
#else
        sprintf(sVar, "Bat: %d", battery_level()); // monta string com valor
#endif
        lcd_goto(64);   // vai para linha 2, coluna 1 do LCD
        lcd_puts(sVar); // mostra no LCD
      break;

      case 2: // sensor de proximidade (funiona igual no simulador e no rob�)
        onlyOnce = 0;    // executa a cada loop
        pwm_off();       // desliga motores se estiverm ligados
        nearSensorData = sensorNear_read();         // leitura do sensor
        sprintf(sVar, "Prox:%03d", nearSensorData); // monta string com valor
        lcd_goto(64);   // vai para linha 2, coluna 1 do LCD
        lcd_puts(sVar); // mostra no LCD
        break;

      case 3: // sensor de linha
        onlyOnce = 0;   // executa a cada loop
        pwm_off();      // desliga motores se estiverem ligados
#ifdef SIMULATOR
        lineSensor.byte = 7; // valor simulado para 1-1-1
#else
        lineSensor.byte = sensorLine_read();// l� valor do sensor de linha
#endif
        sprintf(sVar, "L: %d-%d-%d", lineSensor.part.bit0, lineSensor.part.bit1, lineSensor.part.bit2);
        lcd_goto(64);   // vai para linha 2, coluna 1 do LCD
        lcd_puts(sVar); // mostra no LCD
        break;

      case 4: // bussola
        onlyOnce = 0;    // executa a cada loop
        pwm_off();       // desliga motores se estiverem ligados
        // identificador vai ser 0x3d se estiver funcionando, 0 em caso contr�rio
#ifdef SIMULATOR
        uint8_t compass_id = 0x3d; // valor simulado
#else
        uint8_t compass_id = compass_get_id(); // pega o identificado da b�ssola
#endif
        sprintf(sVar, "Head:%03x", compass_id);  // monta string com valor
        lcd_goto(64);   // vai para linha 2, coluna 1 do LCD
        lcd_puts(sVar); // mostra no LCD
        break;

      case 5: // motores para frente 
        clrbit(onlyOnce, 6); // libera teste 6 para executar
        clrbit(onlyOnce, 7); // libera teste 7 para executar
        if (!testbit(onlyOnce, currentTest)) { // se pode executar
          setbit(onlyOnce, currentTest);       // executa s� uma vez por loop
          pwm_direction(0); // dire��o para frente
          pwm_off();        // desliga motores
          delay_ms(50);     // tem que esperar antes de religar motores pois o pico de corrente reseta o PIC interno
          pwm_on();         // liga motores
          lcd_goto(64);     // vai para linha 2, coluna 1 do LCD
          lcd_puts("Move \x6 \x6"); // mostra no LCD
        }
        break;

      case 6: // motores cw
        clrbit(onlyOnce, 5); // libera teste 5 para executar
        clrbit(onlyOnce, 7); // libera teste 7 para executar
        if (!testbit(onlyOnce, currentTest)) { // se pode executar
          setbit(onlyOnce, currentTest);       // executa s� uma vez por loop
          pwm_direction(3); // gira cw
          pwm_off();        // desliga motores
          delay_ms(50);     // tem que esperar antes de religar motores pois o pico de corrente reseta o PIC interno
          pwm_on();         // liga PWM
          lcd_goto(64);     // vai para linha 2, coluna 1 do LCD
          lcd_puts("Move \x6 \x7"); // mostra no LCD
        }
        break;

      case 7: // motores ccw
        clrbit(onlyOnce, 5); // libera teste 5 para executar
        clrbit(onlyOnce, 6); // libera teste 6 para executar
        if (!testbit(onlyOnce, currentTest)) { // se pode executar
          setbit(onlyOnce, currentTest);       // executa s� uma vez por loop     
          pwm_direction(2); // muda dire��o
          pwm_off();        // desliga motores
          delay_ms(50);     // tem que esperar antes de religar motores pois o pico de corrente reseta o PIC interno
          pwm_on();         // liga PWM
          lcd_goto(64);     // vai para linha 2, coluna 1 do LCD
          lcd_puts("Move \x7 \x6"); // mostra no LCD
        }
        break;

      default: // para motores e retorna para condi��o inicial 
        clrbit(onlyOnce, 5); // libera teste 5 para executar
        clrbit(onlyOnce, 6); // libera teste 6 para executar
        clrbit(onlyOnce, 7); // libera teste 7 para executar
        if (!testbit(onlyOnce, currentTest)) { // se pode executar
          setbit(onlyOnce, currentTest);       // executa s� uma vez por loop     
          pwm_direction(0);  // dire��o em frente
          pwm_off();         // desliga motores
          delay_s(1);        // espera para ver mensagem
          welcome_message(); // recoloca mensagem inicial 
        }
    } // fim - testes 
    delay_ms(100); // espera para dar tempo de ver o lcd
  } // fim - loop principal
} // fim - main
