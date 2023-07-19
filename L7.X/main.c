/*
 * File:   main.c
 * Author: mateus /sophia
 *
 * Created on 25 de Junho de 2023, 00:01
 */


#include <xc.h>

// CONFIG1
#pragma config FOSC = EC       
#pragma config WDTE = OFF     
#pragma config PWRTE = ON      
#pragma config MCLRE = ON     
#pragma config CPD = OFF       
#pragma config BOREN = ON      
#pragma config IESO = ON       
#pragma config FCMEN = ON       
#pragma config LVP = OFF        

// CONFIG2
#pragma config BOR4V = BOR40V   
#pragma config WRT = OFF   



#include <stdio.h>    // para poder usar sprintf()
#include "always.h"   // estruturas e unions úteis (incluir sempre)
#include "delay.h" 
#include "spi.h"      // interface SPI, no robô necessário para LCD e outros
#include "led_rgb.h"  // LED RGB do robô
#include "pwm.h"      //para pwm (funcoes implementadas para o lab 6)
#include "lcd8x2.h"   //para lcd
#include "key.h"      // para utilizar chave da placa
#include "sensor.h"   // sensores de linha, de proximidade e buzzer


char sVar[9];                  
//array auxiliar para printar leitura dos sensores de linha no lcd
volatile union chartype lineSensor; 
//union para armazenar leitura do sensor de linha


void t0_init(void) {            //Funcao de inicializacao do Timer 0
  // o Timer 0 é utilizado para interrupção periódica a cada 5 ms aproximadamente
  OPTION_REGbits.T0CS = 0; // usa clock interno FOSC/4
  OPTION_REGbits.PSA = 0;  // Prescaler para Timer 0 e não para WDT
  OPTION_REGbits.PS = 7;   // ajusta Prescaler para 1:256
  TMR0 = 0xff - 98;        // valor inicial do Timer 0 p/ 5,0176 ms
  T0IE = 1;              // habilita interrupção do Timer 0
}


void welcome_message() {        //Mostra mensagem inicial no display
  lcd_goto(0);           // vai para início da 1a. linha
  lcd_puts("Ativ7");  // mostra string no LCD para saber que está funcionando
  delay_ms(1);           // dá um tempo para o display mostrar a mensagem       
  lcd_goto(64);          // vai para o início da 2a. linha
  lcd_puts("T6G08");        
}

void __interrupt() isr(void) {  // Função geral de tratamento de interrupçãoo
   
    // Timer 0
    // Interrompe a cada 5 ms aproximadamente.
          
    // Controla o tempo de debounce da chave em conjunto com o I-O-C do PORT B
    if (TMR0IE && TMR0IF) {    // se for interrupção do Timer 0
      key_debounce(2); // 2 ciclos são suficientes para 10s de debounce 
      // pois timer interrompe a casa ~5ms
    
      TMR0 = 0xff - 98;   // recarrega contagem no Timer 0 p/ 5,0176ms
      T0IF = 0;         // limpa interrupção
    } // fim - tratamento do Timer 0
    
    if (RBIE && RBIF) { // se for mudança de estado do Port B
      char portB = PORTB;   //caracter armazenando o byte da PORTB
      key_read(portB);    // faz a leitura da chave
      RBIF = 0;           // reseta o flag de interrupção
    } // fim - tratamento I-O-C PORT B
    

    
} // fim - Tratamento de todas as interrupções

int duty_cycle_control(){           //Função de controle do duty cycle 
    // sem parâmetros de entrada, retorna o duty cycle dos motores 
    int nearSensorData  = sensorNear_read();   //leitura do sensor de proximidade 
    int upper_thresh = 480;       //leitura correspondente ao limiar
                                //inferior de deteccao - 4cm 
    int dc = 0;                         //seta duty cycle para zero
    if(nearSensorData <= upper_thresh){     
    //caso distancia seja maior que o limiar <=> 
    //leitura  seja inferior a limiar    
        dc = upper_thresh - nearSensorData;  
        //duty cycle é alto se a leitura do sensor 
        //for baixa e vice versa
    }                                    
    return dc;
}

void follow_line(){     
//função responsavel pelo funcionamento autonomo do robo
//sem parâmetros de entrada e saida
    lineSensor.byte = sensorLine_read(); 
    //armazenando no char 'byte' da union lineSensor
    int duty_cycle = duty_cycle_control();  
    //sensor de proximidade determina o duty cycle dos motores
    int led_color;       //variavel para armazenar a cor dos leds

    sprintf(sVar, "L: %d-%d-%d", lineSensor.part.bit0, lineSensor.part.bit1, 
    lineSensor.part.bit2);     
//armazena leitura do sensor de linha formatada no array sVar
    lcd_goto(0);   // volta para inicio da linha
    lcd_puts(sVar); // mostra no LCD

    pwm_direction(0);       //ambas rodas giram para frente
    if(lineSensor.byte == 0b010){                            //frente - 010
        led_color = (duty_cycle>=100) ? (2:4);    
//se houver obstaculo acende o led com vermelho, c.c. acende com verde
//duty cycle <= 100 significa que a leitura do adc é >= 380 (obstaculo ja esta proximo)
        led_rgb_set_color(led_color);                       //seta cor do led                  
        pwm_set(1, duty_cycle);   
//seta velocidade nos motores correspondente ao duty cycle obtido 
//pelo sensor de proximidade 
        pwm_set(2, duty_cycle);      //ambos os motores tem a mesma velocidade
    }
    else if(lineSensor.byte == 0b011 || lineSensor.byte == 0b001){ 
//curva p/direita - 011 ou 001
        pwm_set(2, duty_cycle/2);               
    //motor direito deve ter velocidade menor
        led_color = (duty_cycle>=100) ? (1:4);   
    //se houver obstaculo acende o led com vermelho, c.c. acende com azul
        led_rgb_set_color(led_color);                     //seta cor do led
        pwm_set(1, duty_cycle);         //motor esquerdo deve ter velocidade maior
    }
    else if(lineSensor.byte == 0b100 || lineSensor.byte == 0b110){      
//curva p/esquerda - 100 ou 110
        pwm_set(1, duty_cycle/2);             
//motor esquerdo deve ter velocidade menor
        led_color = (duty_cycle>=100) ? (3:4);    
//se houver obstaculo acende o led com vermelho, c.c. acende com ciano
        led_rgb_set_color(led_color);               //seta cor do led
        pwm_set(2, duty_cycle);        //motor direito deve ter velocidade maior
    }
    else if(lineSensor.byte == 0b000){        
//nao detecta linha - robo gira para direita na tentativa de encontrar novamente
        pwm_set(2, duty_cycle/2);       //motor direito deve ter velocidade menor
        led_color = (duty_cycle>=100) ? (6:4);   
//se houver obstaculo acende o led com vermelho, c.c. acende com amarelo
        led_rgb_set_color(led_color);                    //seta cor do led
        pwm_set(1, duty_cycle);          //motor esquerdo deve ter velocidade maior                
    }                 
}

void main(void) {
    char keyIn = FALSE; //inicialmente chave não pressionada
    int comecou = 0;        
//variavel binaria para determinar se a chave
//esta sendo pressionada para iniciar ou para parar a atividade

    spi_init();      // inicializa spi para lcd, led_rgb, battery, compass
    led_rgb_init();  // inicializa LED RGB - deve ser comentado para uso no simulador
    lcd_init();      // inicializa lcd
    sensor_init();   // inicializa sensores 
    // Inicializaçõees da placa local
    t0_init();      // inicializa Timer 0 para interrupção periódica de ~5 ms
    pwm_init();     // inicializa PWM
    key_init();     // inicializa chave
    led_rgb_init();     // inicializa LED para debug   

    GIE = 1;    // habilita interrupções
    sensor_power(ON);       //liga sensores

    delay_s(2); // espera para poder ler mensagem de reset
    lcd_clear();      // limpa LCD
    lcd_show_cursor(OFF);  // desliga cursor do LCD 

    while(1){
        keyIn = key_pressed();      //detecta estado da chave
        if(keyIn){     
            if (comecou==1){        
                comecou = 0;   // caso a chave seja pressionada e  
            }                  //a tarefa esteja em execucao deve parar
            else{
                comecou = 1;    //caso a chave tenha sido pressionada e 
            }                   //a tarefa nao esteja em execucao deve iniciar
        }
        if(comecou){
            follow_line();      //executa tarefa se desejado
        }
        else{     //se nao for desejado executar a tarefa
            pwm_set(1, 0);
            pwm_set(2, 0);      //para motores esquerdo e direito
            led_rgb_set_color(0);   //apaga o led
        }
    }
}