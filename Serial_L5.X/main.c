/*
 * File:   main.c
 * Author: sophia/mateus
 *
 * Created on 31 de Maio de 2023, 08:55
 */

// CONFIG1
#pragma config FOSC = EC       
#pragma config WDTE = OFF      
#pragma config PWRTE = ON       
#pragma config MCLRE = ON      
#pragma config CP = OFF         
#pragma config CPD = OFF      
#pragma config BOREN = ON     
#pragma config IESO = ON       
#pragma config FCMEN = ON    
#pragma config LVP = OFF       

// CONFIG2
#pragma config BOR4V = BOR40V  
#pragma config WRT = OFF     

volatile char character;
volatile unsigned char cursor_pos1 = 0; 
// posição do cursor do LCD na primeira linha
volatile unsigned char cursor_pos2 = 64; 
// posição do cursor do LCD na segunda linha
int n_interrupt = 200;
// número de interrupçoes que define o tempo para a  apresentação 
// dos caracteres no LCD
volatile int tick = 0; 
// variável que conta o número de interrupçoes do Timer 0

#include <xc.h>

// Includes do projeto
#include <stdio.h>    // para poder usar sprintf()
#include "always.h"   
#include "delay.h" 

#include "spi.h"
#include "battery.h" 
#include "lcd8x2.h"
#include "serial.h"   
#include "key.h"  
#include "sensor.h"  

#define BUZZER RB7   // bit para buzzer


void t0_init(void) {
  OPTION_REGbits.T0CS = 0; // usa clock interno FOSC/4
  OPTION_REGbits.PSA = 0;  // Prescaler para Timer 0 
  OPTION_REGbits.PS = 7;   // ajusta Prescaler para 1:256
  TMR0 = 0xff - 98;        // valor inicial do Timer 0 p/ 5,0176 ms
  T0IE = 1;              // habilita interrupção do Timer 0
}


void buzzer_init(void) {
 TRISB7 = 0;  // RB7 é saída para BUZZER 
 BUZZER = 0; 
}

void __interrupt() isr(void) {  // Função geral de tratamento de interrupção
   
    // Timer 0
    // Interrompe a cada 5 ms aproximadamente.

    if (TMR0IE && TMR0IF) {  
      key_debounce(2); // 
      tick++;  // incremento na contagem de interrupçoes
      TMR0 = 0xff - 98;   // recarrega contagem no Timer 0 p/ 5,0176ms
      T0IF = 0;         // limpa flag
    } // fim - tratamento do Timer 0
    
} // fim - Tratamento de todas as interrupcoes


void beep() {
  BUZZER = ON;        // liga buzzer
  delay_s(4);  // por 4s
  BUZZER = OFF;       // desliga buzzer
}

void welcome_message() {
  lcd_goto(0);           // vai para início da 1a. linha
  lcd_puts("Ativ5");  // mostra string no LCD para saber que est? funcionando
  delay_ms(1);           // d? um tempo para o display mostrar a mensagem       
  lcd_goto(64);          // vai para o in?cio da 2a. linha
  lcd_puts("T6G08");        // coloca no. da vers?o  
}


void main(void) {
    char keyIn = FALSE;
    character = '0';
    char recebido;
    lcd_init(); 
    sensor_init(); //para inicializar buzzer
    t0_init();
    serial_init();
    key_init();     // inicializa chave
    spi_init();             //inicializa spi
    buzzer_init();          //inicializa buzzer


    GIE = 1;    // habilita interrupçoes  
    sensor_power(ON);
    delay_s(2); // espera para poder ler mensagem de reset
    lcd_clear();      // limpa LCD
    lcd_show_cursor(OFF);  // desliga cursor do LCD 

    welcome_message();
    beep();
    lcd_clear();
    delay_ms(500);
    lcd_goto(0);
    delay_ms(500);


    while(1){
        recebido = chkchr(); 
        //checa de forma não bloqueante se há um caracter no buffer de recepção
        
        keyIn = key_pressed();      //guarda estado da chave 
        if (character == ':'){ // : é o proximo char depois de 9
            character = 'A';
        }
        if (character == '['){ // [ é o proximo char depois do Z
            character = '0';
        }
        if (tick >= n_interrupt){  
        // se chegar ao número de interrupçoes definido
            lcd_goto(cursor_pos1); 
            // cursor vai para a proxima posição não escrita na primeira linha
            delay_ms(1);  // tempo  para o LCD estabilizar
            character++;  // atualiza qual o proximo caracter a ser escrito
            lcd_putchar(character);  // escreve o proximo caracter do loop
            tick = 0;  // recomeça a contagem de interrupçoes
        }

        if (keyIn == 1){  // se a chave for pressionada
            putch(character); // Manda o caracter pela comunicação serial
            delay_ms(500);
            lcd_goto(++cursor_pos1);  // Move o cursor do LCD para frente
        }
        if (recebido != 255){  // se for recebido algum caracter
            lcd_goto(cursor_pos2++);  // cursor vai para a segunda linha
            delay_ms(1);  // tempo  para o LCD estabilizar
            lcd_putchar(recebido);  // escreve o caracter recebido no LCD
            delay_ms(1);
        }               
        
    }
    return;
}