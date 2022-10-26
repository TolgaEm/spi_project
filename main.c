

#include "stm32f10x.h"                  // Device header

/*
*   PB12->NSS
*		PB13->SCK
*		PB14->MISO
*		PB15->MOSI     */



void GPIO_config();
void SPI2_config();
void send_data(uint8_t *,uint8_t );

int main() {
	
	int data[] ={12,1,4,'a'};
	
	GPIO_config();
	SPI2_config();
	
	
	
	while(1){ 
		
		send_data(data,4);
		
	}
	
}


void GPIO_config(){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOA->CRH = 0X99900000;
	
}

void SPI2_config(){
	
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	SPI2->CR1 = 0;
	SPI2->CR1 |= SPI_CR1_SPE | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI;
	
}

void send_data(uint8_t *data,uint8_t len){
	
		uint8_t i=0;
		SPI2->SR = 0;
	
	while(i<len){
		while(!(SPI2->SR & SPI_SR_TXE));
		SPI2->DR = data[i];
		i++;
	}
}

