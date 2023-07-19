
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

#include <stdio.h>   
#include "always.h"  
#include "delay.h"   
#include "spi.h"     
#include "pwm.h" 
#include "lcd8x2.h"
#include "sensor.h"  

volatile int tick = 0; 
// variável que conta o número de interrupçoes do Timer 0

// Variáveis de conversão de leitura do sensor para distância
long k = 20;  // variável de linearização
long m = 31993;  // coeficiente angular da relação linearizada voltagemXdistancia
long a  = 50;  // coeficiente linear da relação linearizada voltagemXdistancia

volatile unsigned int adc_result = 0;  
//variável volátil para armazenar o resultado da conversão

//contador do encoder do motor 1
volatile signed int encoder1_counter = 0;     
//contador do encoder do motor 2
volatile signed int encoder2_counter = 0;     
// estado atual do encoder do motor 1
volatile signed char encoder1_state = 0;
// estado anterior do encoder do motor 1
volatile signed char encoder1_state_old = 0;
// estado atual do encoder do motor 2
volatile signed char encoder2_state = 0;
// estado anterior do encoder do motor 2
volatile signed char encoder2_state_old = 0;

// Matriz de transição de estados dos encoders na memória
__EEPROM_DATA(0x00,0x01,0xFF,0x00,0xFF,0x00,0x00,0x01);
//endereco 0 - transicao 0 p/ 0
//endereco 1 - transicao 0 p/ 1
//endereco 2 - transicao 0 p/ 2 
//endereco 3 - transicao 0 p/ 3 
//endereco 4 - transicao 1 p/ 0 
//endereco 5 - transicao 1 p/ 1 
//endereco 6 - transicao 1 p/ 2 
//endereco 7 - transicao 1 p/ 3 
__EEPROM_DATA(0x01,0x00,0x00,0xFF,0x00,0xFF,0x01,0x00); 
//endereco 0 - transicao 2 p/ 0
//endereco 1 - transicao 2 p/ 1
//endereco 2 - transicao 2 p/ 2 
//endereco 3 - transicao 2 p/ 3 
//endereco 4 - transicao 3 p/ 0 
//endereco 5 - transicao 3 p/ 1 
//endereco 6 - transicao 3 p/ 2 
//endereco 7 - transicao 3 p/ 3 

void t0_init(void) {    //inicialização do timer 0
  // o Timer 0 utilizado para interrupção periódica a cada 5 ms aproximadamente
  OPTION_REGbits.T0CS = 0; // usa clock interno FOSC/4
  OPTION_REGbits.PSA = 0;  // Prescaler para Timer 0
  OPTION_REGbits.PS = 7;   // ajusta Prescaler para 1:256
  TMR0 = 0xff - 98;        // valor inicial do Timer 0 p/ 5,0176 ms
  T0IE = 1;              // habilita interrupção do Timer 0
}


void ioc_init(){    //inicialização do IoC na porta B   


   TRISB1 = 1; //seta canais dos encoders para entrada
   TRISB2 = 1;
   TRISB3 = 1;
   TRISB4 = 1;
   
   ANS8= 0;
   ANS9 = 0;
   ANS10 = 0; //configura canais como entradas digitais 
   ANS11 = 0;
   
   WPUB1 = 0;
   WPUB2 = 0;
   WPUB3 = 0;   //desabilita controles individuais de pull ups
   WPUB4 = 0;
   
   IOCB1 = 1;
   IOCB2 = 1;   //habilita IoC dos bits correspondentes aos canais dos encoders
   IOCB3 = 1;
   IOCB4 = 1; 
   
   RBIE = 1;    // habilita interrupção da Porta B
}//pino RB4 - ENC_A1, RB3 - ENC_B1, RB2 - ENC_A2, RB1 - ENC_B2



void __interrupt() isr(void) {  //Funcao geral de interrupçoes
   
    // Timer 0
    // Interrompe a cada 5 ms aproximadamente.
        
    if (TMR0IE && TMR0IF) {   
      TMR0 = 0xff - 98;   
      // recarrega contagem no Timer 0 p/ 5,0176ms
      T0IF = 0;        
      tick++;
    } // fim - tratamento do Timer 0
    
    if (RBIE && RBIF) { // se for mudança de estado do Port B
      char portB = PORTB;   //caracter armazenando o byte da PORTB
      encoder1_state = (portB & 0b00011000) >> 3;      
      // estado do encoder do motor 1 é guardado
      encoder2_state = (portB & 0b00000110) >> 1;       
      // estado do encoder do motor 2 é guardado
      encoder1_counter += (signed char) EEPROM_READ(4*encoder1_state_old + encoder1_state);
      encoder2_counter += (signed char) EEPROM_READ(4*encoder2_state_old + encoder2_state);
      // incremento dos encoders de acordo com a matriz 
      //de transição de estados guardada na EEPROM
      encoder1_state_old = encoder1_state;
      encoder2_state_old = encoder2_state;
//atualiza estados anteriores dos encoders
      RBIF = 0;    // reseta o flag de interrupï¿œï¿œo
    } // fim - tratamento I-O-C PORT B
    
} // fim - Tratamento de todas as interrupï¿œï¿œes

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

void set_vel(int dist){
    //Controle da velocidade em função da distância
    int dc = 0; // duty cycle
    if (dist > 350){ 
    // se a distância é grande o duty cycle é máximo
    // sendo que o máximo utilizado é 60%
        dc = 600;
    }
    else if(dist < 50){
        // se a distância é pequena, os motores devem parar
        dc = 0;
    }
    else{
        dc = dist + 250;  // se dist = 50mm, vel=0
        // o duty cycle cresce linearmente com a distância lida pelo sensor
    }
    pwm_set(1, dc);
    pwm_set(2, dc);
    
}

void main(void) {
    // Inicializações
    spi_init(); 
    lcd_init(); 
    sensor_init(); 
    t0_init();
    pwm_init();
    ioc_init();
    // Habilita interrupções
    GIE = 1;    

    sensor_power(ON);
    delay_s(2); // espera para poder ler mensagem de reset
    lcd_clear();      
    lcd_show_cursor(OFF);  // desliga cursor do LCD 

    // Velocidades dos motores
    int v_dir = 0;
    int v_esq = 0;
    char printvel[30]; // guarda as velocidades a serem mostradas no LCD
    int dist;// recebe a distâcia calculada
    char distance[20];  // recebe a distancia a ser mostrada no display
    char encoderchar[20];
    // posição inicial dos encoders para cálculo da velocidade
    signed int initpos_dir = encoder1_counter;
    signed int initpos_esq = encoder2_counter;
    
    while (1){
        // Medição  de velocidade das rodas
        if (tick >= 20){  // a cada 100ms
            tick = 0;
            // cada incremento do contador do encoder equivale a
            // um deslocamento de 2,75 mm aproximado para 3 mm
            // Velocidade em mm/s do motor direito
            v_esq = 30*(encoder1_counter - initpos_esq); 
            // Velocidade em mm/s do motor esquerdo
            v_dir = 30*(encoder2_counter - initpos_dir);
            // Apresentação das velocidades no LCD
            sprintf(printvel, "%d %d", v_esq, v_dir);
            lcd_goto(0); // move o cursor do LCD para o começo da 2a linha
            lcd_puts(printvel);
            initpos_esq = encoder1_counter;
            initpos_dir = encoder2_counter;
            } 
       
        // Leitura da distância do sensor analogico
        adc_result = sensorNear_read(); // guarda a leitura do sensor
        dist = calc_dist(adc_result);  // calcula a distância correspondente
        sprintf(distance, "d %d mm", dist);   
        // atualiza a string a ser mostrada
        lcd_goto(64);    // move o cursor do LCD para 1.a linha novamente
        lcd_puts(distance);     // mostra a distância no LCD

        //Inicialmente testar estimativa de velocidade com encoder
        //pwm_direction(2);
        //pwm_set(1, 100);
        //pwm_set(2, 100);
        //pwm_set(1, 200);
        //pwm_set(2, 200);
        //pwm_set(1, 300);
        //pwm_set(2, 300);
        //pwm_set(1, 400);
        //pwm_set(2, 400);
        //pwm_set(1, 500);
        //pwm_set(2, 500);
         
        //Após calibração: mudar a velocidade de acordo com a distância
        set_vel(dist);
    }

    return;
}
        