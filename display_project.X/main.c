/*
 * File:   main.c
 * Author: 
 * Celina Lee
 * Gabriela Ishikawa
 * Mateus Salomão 11914789
 * Pedro Fuoco 
 * Sophia Celine
 * 
 * 
 * 
 *
 * Created on 26 de Junho de 2022, 11:53
 */

// PIC16F886 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = EC        // Oscillator Selection bits (EC: I/O function on RA6/OSC2/CLKOUT pin, CLKIN on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include<xc.h>
#include<stdio.h>
#include "delay.h"

//Defines
#define _XTAL_FREQ 20000000 // define a frequencia do clock em MHz
// Produz atraso em ms, time < 50.463.240
//__delay_ms(time)
// Produz atraso em us, time < 50.463.240
//__delay_us(time)





//EEPROM
// mudar de 0xff para o seu c?digo.
__EEPROM_DATA(0b01111110, 0b00110000, 0b01101101, 0b01111001, 0b00110011, 0b01011011, 0b01011111, 0b01110000); // carrega na EEPROM os bytes de 0 a 7
__EEPROM_DATA(0b01111111, 0b01110011, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff); // carrega na EEPROM os bytes de 8 a 15




//Vari�veis globais (Lembrando que s�o vol�teis se usadas em interrup��o)
//   colocar seu c�digo aqui
volatile unsigned int adc_resultado;


//Inicializa��o do Timer0
void timer0_init(void) {
  // o Timer 0 � utilizado para interrup��o peri�dica a cada 5 ms aproximadamente
  OPTION_REGbits.T0CS = 0; // usa clock interno FOSC/4
  OPTION_REGbits.PSA = 0;  // Prescaler � para Timer 0 e n�o para WDT
  OPTION_REGbits.PS = 7;   // ajusta Prescaler para 1:256
  TMR0 = 0xff - 98;        // valor inicial do Timer 0 p/ 5,0176 ms
  T0IE = 1;                // habilita interrup��o do Timer 0
}

//Inicializa��o do ADC
void adc_init(void) { 
    TRISA0 = 1;  //configura pino 2 como input
    ANS0 = 1;  //configura pino 2 como entrada anal?gica 
    ADCS1 = 1;  //Fosc/32
    ADCS0 = 0;  //Fosc/32
    VCFG1 = 0;  //Vref- = Vss = 0V
    VCFG0 = 0;  //Vref+ = Vdd = 5V
    ADCON0bits.CHS = 0b0000;  //Seleciona AN0
    ADFM = 1;  //justificado a direita
    ADON = 1;  //liga conversor
    __delay_us(10);  //espera 10us
    adc_resultado = 0;  //atribui valor 0 para variavel global adc_resultado 
}
//Leitura do ADC -> retorna entre 0 e 1023 em int sem sinal
unsigned int adc_read(void) {
    GO_nDONE = 1;  //set bit GO_nDONE em 1 para come?ar convers?o
    while (GO_nDONE);  //espera a convers?o terminar, ou seja, GO_nDONE virar 0
    unsigned int ADC_result = ADRESH*256+ADRESL;  //atribui o valor do registrador ADRESH*256+ADRESL na variavel global adc_resultado
    ADIF = 0;//Clear na flag de interrup??o do ADC 
    
    return ADC_result;
}
//Inicializa��o do display -> setar portas B e C como sa�da e Porta B como digital e dar valor inicial )
void display_init(void) {
    TRISB &= 10000000;
    
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    TRISC3 = 0;
    
    ANS8 = 0;
    ANS9 = 0;
    ANS10 = 0;
    ANS11 = 0;
    ANS12 = 0;
    ANS13 = 0;
    
    // reseta os valores de sa�da
    PORTB = 0;
    RC0 = 0;
    RC1 = 0;
    RC2 = 0;
    RC3 = 0;
}
//Escreve o n�mero "number" no digito "sel" (de 0 a 3) display usando o mapa na EEPROM
void display_put(int number, char sel) {
    PORTC &= 0b11110000;
    if (sel == 0){
        PORTCbits.RC0 = 1;
    }
    else if (sel == 1){
        PORTCbits.RC1 = 1;
    }
    else if (sel == 2){
        PORTCbits.RC2 = 1;
    }
    else if (sel == 3){
        PORTCbits.RC3 = 1;
    }
    PORTB = eeprom_read(number);
    __delay_ms(5);
}

// Fun��o para tratamento de interrup��es
// Leitura do A/D, a cada 5ms, com Timer0
void interrupt isr(void) {
  // Tratamento da interrup��o do Timer 0
  if (T0IE && T0IF) {
    // Interrup��o do Timer 0 aqui
    adc_resultado = adc_read();
    TMR0 = 255 - 98; // recarrega contagem do Timer 0
    T0IF = 0;  // limpa interrup��o
  }
  // Tratamento de outras interrup��es aqui
}

void main(void) {    
    timer0_init();
    adc_init();
    display_init();
    GIE=1;
    //   colocar seu c�digo aqui (inicializar vari�veis do main))
    
    unsigned int leitura = 0;
    unsigned int milhar = 0;
    unsigned int centena = 0;
    unsigned int dezena = 0;
    unsigned int unidade = 0;
    
    while(1){
    // Resolve os 4 d�gitos da leitura do ADC
    // usa display_put(number,sel) para colocar cada um dos 4 d�gitos no display
        leitura = adc_resultado;
        milhar = leitura / 1000;
        leitura = leitura % 1000;
        centena = leitura / 100;
        leitura = leitura % 100;
        dezena = leitura / 10;
        unidade = leitura % 10;
        
                
        display_put(unidade, 0);
        display_put(dezena,  1);
        display_put(centena, 2);
        display_put(milhar,  3);
    }
}