/*
 * SPI.h
 *
 * Created: 9/5/2017 8:34:54 PM
 * 
 */ 


#ifndef SPI_H_
#define SPI_H_

#define SS 4
#define MOSI 5
#define SCK 7
#define MISO 6

void SPI_MasterInit(void);
void SPI_MasterTransmit(char Data);

void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);

#endif /* SPI_H_ */