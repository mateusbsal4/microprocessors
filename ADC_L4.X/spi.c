/* 
 * File:     spi.h 
 * Author:   Bruno Alan Miyamoto ou Thiago ?
 * Date:     7/02/2016
 * Comments: Controla interface SPI
 * Revision history:
 *           [jo:160214] c�digo comentado e alguns ajustes 
 */

#ifndef SPI_C
#define	SPI_C

#include "spi.h"
#include "always.h"

#define SS RC0          // SS para SPI
#define DUMMYDATA 0
#define DATA_READY RB0  // Pino de entrada para receber indica��o de que h� um byte para ser lido por SPI

///
/// inicializa a comunicacao spi em modo 0, 0
///
void spi_init(){
  ANS12 = DIGITAL;     // RB0 � digital
  TRISB0 = INPUT;      // RB0 � entrada (DRDY)
  TRISC0 = OUTPUT;     // RC0 para sa�da (SS)
  TRISC3 = OUTPUT;     // RC3 para sa�da (SCK)
  TRISC4 = INPUT;      // RC4 para entrada (SDI)
  TRISC5 = OUTPUT;     // RC5 para sa�da (SDO)
  SS = 1;              // SS inativo 
  SSPEN = 0;           // desabilita modo SPI
  CKP = 0;             // estado inativo � n�vel LOW
  CKE = 0;             // dado transmitido na borda se subida do SCK
  SMP = 0;             // dado de entrada amostrado no meio do tempo do dado de sa�da
  SSPCONbits.SSPM = 1; // SPI em modo Master, clock = FOSC/16
  SSPEN = 1;           // habilita modo SPI  
}

///
/// Envia e recebe dado pelo SPI
/// @param data dado a ser transmitido
/// @return retorna dado recebido
///
uint8_t spi_exchange(uint8_t data){
  WCOL = 0;       // limpa flag de colis�o
  SS = 0;         // sele��o de SPI ativado
  SSPBUF = data;  // transfere dado para o buffer do SPI
  while(SSPSTATbits.BF == 0); // enquanto o buffer n�o tiver recebido dado, espera
  SS = 1;         // recebeu dado, iniativa sele��o
  return SSPBUF;  // retorna o dado recebido
}


///
/// Faz a leitura de dados por SPI
/// @return retorna dado
///
uint8_t spi_read(){
  
  while (!DATA_READY); // espera os dados estarem prontos para serem lidos
  
  return spi_exchange(DUMMYDATA);
}


///
/// Envia dados por SPI
/// @param data - dado a ser transmitido
///
void spi_write(uint8_t data){
  spi_exchange(data);
}
#endif