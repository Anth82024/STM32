#include "stm32f1xx_hal.h"

#define usart USART3   //USARTx - Channel
#define tim TIM3   //TIMx - Timer
#define max 30 //Size of buffer bank. Warring !!! It's HEX-number
#define send GPIOB->ODR|=GPIO_PIN_2; //Enable to send PIN 
#define wait GPIOB->ODR&=~GPIO_PIN_2; //Waiting for massage PIN

typedef struct
{	
  uint8_t TxData[255];    // output
	uint8_t RxData[255];    // input
	uint8_t cnt;            // bit counter
	
	uint8_t adress;         // MB adress
	
} mb;


uint16_t crc16(uint8_t *adr_buffer, uint32_t byte_cnt);
void poll (mb *mb); // To USART_IRQHandler
void mb_handler (mb *mb, uint16_t *bank, UART_HandleTypeDef* uart); // To USART_IRQHandler and TIMx_IRQHandler 
void mb_init (mb *mb, uint8_t adress, uint16_t arr, uint16_t psc);

//Example for slave
//UART_HANDLER
/*
  poll(&mb);
*/
//TIM_HANDLER
/*
mb_handler(&mb, bank, &huartx);
*/
//----------------------------------------------------------------------
//Method for calculating timer's settings
/*----------------------------------------------------------------------

     SPEED
Baud    Bit    byte  [us]
4800	  208	   2083
9600	  104	   1042
19200	  52	   521
38400	  26	   260
57600	  17	   174
115200	8,7	   87



Control time 1,2-1,5 byte

Calc: Timer_ARR = Timer_Freq[MHz] x 1.2(1.5) x byte[us] 

USARTx->CR1|=USART_CR1_RXNEIE - activate interrupt by Rx

------------------*/

