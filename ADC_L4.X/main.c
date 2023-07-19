#include <xc.h>

// CONFIG1
#pragma config FOSC = EC        
#pragma config WDTE = OFF       
#pragma config PWRTE = ON       
#pragma config MCLRE = ON       
#pragma config CP = OFF             
#pragma config CPD = OFF        
#pragma config BOREN =OFF     //bits de configuração  
#pragma config IESO = ON        
#pragma config FCMEN = ON       
#pragma config LVP = OFF        

// CONFIG2
#pragma config BOR4V = BOR40V   
#pragma config WRT = OFF        

#include <stdio.h>    // para poder usar sprintf()
#include "always.h"   // estruturas e unions ?teis (incluir sempre)
#include "delay.h"    // para atrasos
#include "spi.h"      // interface SPI, no rob? necess?rio para LCD e outros
#include "lcd8x2.h"   // para usar o LCD, no rob? ? necess?rio o SPI
#include "key.h"      // para utilizar chave da placa
#include "sensor.h"   // sensores de linha, de proximidade e buzzer
#include "adc.h"        //para utilizar o conversor AD
#include "serial.h"     
#include "led_rgb.h"     //para utilizar o led
#define BUZZER RB7   // bit para buzzer
#define LED RB5



//CALIBRATION CODE//



volatile unsigned int adc_result = 0;  
//variável volátil para armazenar o resultado da conversão
volatile unsigned int n_read = 0;  
// variável que guarda o número de leituras efetuadas pelo sensor


void t0_init(void) { // inicializa interrupção do Timer 0
  OPTION_REGbits.T0CS = 0; // usa clock interno FOSC/4
  OPTION_REGbits.PSA = 0;  // Prescaler para Timer 0 e não WDT
  OPTION_REGbits.PS = 7;   // ajusta Prescaler para 1:256
  TMR0 = 0xff - 98;        // início da contagem em 98
  TMR0IE = 1;              // habilita interrupçãoo do Timer 0
}

void buzzer_init(void) {    //função de inicialização do buzzer
 TRISB7 = 0;  // RB7 configurado como saída para BUZZER 
 BUZZER = 0;    //buzzer desligado
}


void __interrupt() isr(void) {  // Função geral de tratamento de interrupçãoo
   
    // Timer 0
    // Interrompe a cada 5 ms aproximadamente.
          
    // Controla o tempo de debounce da chave em conjunto com o I-O-C do PORT B
    if (TMR0IE && TMR0IF) {    // se for interrupção do Timer 0
      key_debounce(2); // 2 pois timer interrompe a casa ~5ms
      
      static int tick = 0;     
      // contador de vezes que o Timer 0 interrompe
      if( ++tick >=50){   
      //se interrupção ocorreu 50 vezes, ou seja, passados 50*5ms 
      // (0,25s), uma nova leitura do sensor é efetuada e incorporada à somatória
        tick = 0;                       //contador é resetado
        adc_result += sensorNear_read(); // leitura do sensor - chama adc_read(0);
        n_read ++;                      //número de leituras é incrementado
      }
      TMR0 = 0xff - 98;   // recarrega contagem no Timer 0 p/ 5,0176ms
      TMR0IF = 0;         // limpa interrupção
    } // fim - tratamento do Timer 0
    
    if (RBIE && RBIF) { // se for mudança de estado do Port B
      char portB = PORTB;   //caracter armazenando o byte da PORTB
      key_read(portB);    // faz a leitura da chave
      RBIF = 0;           // reseta o flag de interrupção
    } // fim - tratamento I-O-C PORT B
    

    
} // fim - Tratamento de todas as interrupções

void beep() {       //função para produzir um som por 0,3s
  BUZZER = ON;        // liga buzzer
  delay_big_ms(300);  // por 0,3s
  BUZZER = OFF;       // desliga buzzer
}

void led_init(){       //função de inicialização do LED
    TRISB5 = 0;         //configura RB5 como saída
    ANS13 = 0;          //configura a saída RB5 como digital digital 
    LED = 0;            //desliga o led
}

void welcome_message() {  //mostra grupo e turma no display
  lcd_goto(0);           // vai para início da 1a. linha
  lcd_puts("Ativ4");  // mostra string no LCD para saber que est? funcionando
  delay_ms(1);           // dá um tempo para o display mostrar a mensagem       
  lcd_goto(64);          // vai para o início da 2a. linha
  lcd_puts("T6G08");        // coloca no. da versão  
}


void main(void) {
    char result[10];    //array de caracteres para //armazenar o resultado da conversão
    char keyIn = FALSE; //variável que guarda o estado da chave
    lcd_init();      // inicializa lcd
    sensor_init();   // inicializa sensores (adc_init(0) chamado aqui)
    t0_init();
    serial_init();  // inicializa canal de comunicação serial
    key_init();     // inicializa chave
    spi_init();             //inicializa spi para lcd, led_rgb, battery, compass
    buzzer_init();          //inicializa buzzer
    led_init();         //inicializa led
    
    GIE = 1;    // habilita interrup??es
    
    sensor_power(ON);       //liga o sensor
                     
  // LCD
    delay_s(2); // espera para poder ler mensagem de reset
    lcd_clear();      // limpa LCD
    lcd_show_cursor(OFF);  // desliga cursor do LCD 

  // mensagem inicial no LCD 
    welcome_message(); // coloca mensagem inicial no LCD 
    delay_s(2);
    while(1){
      keyIn = key_pressed();        //retorna estado da chave (pressionada ou não)
      if(keyIn){
        n_read = 0;         
        //se a chave foi pressionada reseta o número de leituras e o resultado
        adc_result = 0;
      } 
      if(n_read == 10){   
      // se o número de leituras 
            sprintf(result, "%d", (adc_result/10));     
            //armazena os caracteres correspondentes aos dígitos da média
            //aritmética truncada das 10 leituras no array de caracteres "result"
            lcd_clear();            //limpa o lcd
            lcd_puts(result);       //mostra no lcd
            beep();                 //da um beep para sinalizar a leitura
            LED = ~LED;             //inverte o estado do led para sinalizar a leitura
        }
      
    }
}    


// DATA PRESENTATION CODE //
/*
// Variáveis de conversão de leitura do sensor para distância
long k = 20;  // variável de linearização
long m = 31993;  // coeficiente angular da relação linearizada voltagemXdistancia
long a  = 50;  // coeficiente linear da relação linearizada voltagemXdistancia

volatile unsigned int adc_result = 0;  
//variável volátil para armazenar o resultado da conversão

void t0_init(void) { // inicializa interrupção do Timer 0

  OPTION_REGbits.T0CS = 0; // usa clock interno FOSC/4
  OPTION_REGbits.PSA = 0;  // Prescaler para Timer 0 e não para WDT
  OPTION_REGbits.PS = 7;   // ajusta Prescaler para 1:256
  TMR0 = 0xff - 98;        // valor inicial do Timer 0 p/ 5,0176 ms
  TMR0IE = 1;              // habilita interrupção do Timer 0
}

void welcome_message() {
  lcd_goto(0);           // vai para início da 1a. linha
  lcd_puts("Ativ4");  // indicação da atividade
  delay_ms(1);           // tempo para o display mostrar a mensagem       
  lcd_goto(64);          // vai para o início da 2a. linha
  lcd_puts("T6G08");        // número do grupo e da turma 
}

int calc_dist(int leitura){ 
    // Função de conversão da leitura do sensor para distância em mm
    // Equação de conversão é do tipo d = m/(L + a) - k, em que
    // m é a inclinação da reta (distanciaXleitura) e a é o coeficiente linear
    // k é a variável de linearização: d -> 1/(d+k)
    // L é a leitura do sensor
    // d é a distãncia correspondente à leitura
    int dist; // variável para a distância
    // tratamento para evitar divisão por zero caso a<0
    if(a < 0){  
        if (((long)leitura + a)==0){
            dist = 0;
        }
    }
    else{  // caso geral de conversão
        dist = (int)(m/((long)leitura + a)) - (int)k;
    }
    
    return dist;
}

void main(void) {
    lcd_init();      // inicializa lcd
    sensor_init();   // inicializa sensores 
    t0_init();       // inicializa o Timer 0 
    serial_init();  // inicializa canal de comunicação serial
    key_init();     // inicializa chave
    spi_init();
    
    sensor_power(ON);
    int dist; // recebe a distâcia calculada
    char distance[10];  // recebe a distancia a ser mostrada no display
    // LCD
    delay_s(2); // espera para poder ler mensagem de reset
    lcd_clear();  // limpa o LCD
    lcd_show_cursor(OFF);  // desliga cursor do LCD 
    
    welcome_message();      // mensagem inicial no LCD 

    while(1){  // looop principal
        
        adc_result = sensorNear_read();     // guarda a leitura do sensor
        dist = calc_dist(adc_result);       // calcula a distância correspondente
        sprintf(distance, "%d mm", dist);   // atualiza a string a ser mostrada
        lcd_goto(0);    // move o cursor do LCD para o começo da 1a linha
        lcd_puts(distance);     // mostra a distância no LCD
        delay_big_ms(300);  
      
    }
    return;
}
*/