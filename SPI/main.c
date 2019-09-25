

#include "stm32f10x.h"                  // Device header
#include "delay.h"

int durum;
char deger;

void Pin_Ayarlari(void);
void SPI_Master_Ayar(void);
void  veri_Gonder(uint8_t veri);


int main()
{
	
	
	Pin_Ayarlari();
	SPI_Master_Ayar();
	delay_init();
	
	while(1)
	{
		
		durum=GPIOB->IDR & 0x00000001;	//BUTON OKUMA.
		GPIOA->BRR |=1<<3;
		
	/* if(durum)
		 deger='1';
	 else
		 deger='0';*/
	 
	 
		veri_Gonder(durum);
    delay_ms(10);
  //  GPIOA->BSRR |=1<<3;		
		
		
		
	 /* GPIOA->BSRR = 0x00100000;//NSS LOW.
		veri_Gonder(1);
		//GPIOA->BSRR = 0x00000010;//NSS HIGH.
		delay_ms(10);
		
		
		
		
		
	  //GPIOA->BSRR = 0x00100000;//NSS LOW.
		veri_Gonder(0);
		delay_ms(10);
		GPIOA->BSRR = 0x00000010;//NSS HIGH.
		*/
		
		
	
	}



  

}

void Pin_Ayarlari(void)
{
	RCC->APB2ENR   |=1<<2;//A portu aktif.
	RCC->APB2ENR   |=1<<3;//B portu aktif. 
	RCC->APB2ENR   |=1<<0;//AFIO aktif.
	
	//NSS ,SCK ,MOSI => Alternatif push-pull
	//MISO =>   Input floating.50 mhz
	
	GPIOA->CRL    = 0xB4B03000; //pa3 
	GPIOB->CRL    = 0x00000008;//B0 buton(pull-down).
	

}

void SPI_Master_Ayar()
{
	RCC->APB2ENR |=1<<12;//SPI clock aktif.
	SPI1->CR1     &=~(1<<3); //FCLK/2
	SPI1->CR1     &=~(1<<4);//FCLK/2
	SPI1->CR1     &=~(1<<5);//FCLK/2
	SPI1->CR1     &=~(1<<0);//CPHA 0.
	SPI1->CR1     &=~(1<<1);//CPOL 0.
	SPI1->CR1     &=~(1<<11);//8 bit formati.
	SPI1->CR1     &=~(1<<7);//MSB first.
	//SPI1->CR2    |=1<<2;//NSS output.(SSOE)
	SPI1->CR1    |=1<<9;//SSM set.
	SPI1->CR1     |=1<<2;//MSTR aktif.
	
	
	
}

void veri_Gonder(uint8_t veri)
{
	 SPI1->CR1     |=1<<6;//SPI aktif.
   SPI1->DR  = veri;
	 while(!(SPI1->SR & (1<<1)));//TXE nin 1 olmasini bekle.
	// while(SPI1->SR & (1<<7)); //BSY 0 OLMASINI BEKLE
  // SPI1->CR1     &=~(1<<6);//SPI pasif. 	
	
	 
	
	/* 
	SPI1->CR1 |= 1 << 6;									// Enable SPI1 module
	while(!(SPI1->SR & 2));								// Wait until Transfer buffer empty
	GPIOA->BSRR = 0x00100000;							// Assert slave select, RM0008 datasheet'de sadece word olarak erisime izin veriyor.
	SPI1->DR = veri;											// Write data
	while(SPI1->SR & 0x80);								// Wait for transmission done
	GPIOA->BSRR = 0x00000010;
	
	
	*/
	
}

