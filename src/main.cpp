#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "CppUTest/CommandLineTestRunner.h"

void systemInit()
{
   /**
    *  IMPORTANT NOTE!
    *  The symbol VECT_TAB_SRAM needs to be defined when building the project
    *  if code has been located to RAM and interrupts are used.
    *  Otherwise the interrupt table located in flash will be used.
    *  See also the <system_*.c> file and how the SystemInit() function updates
    *  SCB->VTOR register.
    *  E.g.  SCB->VTOR = 0x20000000;
    */

}

void uartInit(uint32_t baudrate)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   USART_InitTypeDef USART_InitStructure;

   //Enable GPIOC clock
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
   //Enable USART6 clock
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

   //Configure USART6_TX (PC6) and USART6_RX (PC7)
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   //Remap USART6_TX and USART6_RX pins to PC6 and PC7
   GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
   GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

   //Configure USART6
   USART_InitStructure.USART_BaudRate = baudrate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   USART_Init(USART6, &USART_InitStructure);

   //Enable USART6
   USART_Cmd(USART6, ENABLE);
}

/**
 * @brief Send character with UART
 * @param[in] c The character to be written
 * @return the character written is returned.
 **/
int putchar(int c)
{
   //Wait for the transmitter to be ready
   while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);

   //Send character
   USART_SendData(USART6, c);

   //Wait for the transfer to complete
   while(USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);

   //On success, the character written is returned
   return c;
}

void ioInit()
{
   /* Initialize LEDs */
   STM_EVAL_LEDInit(LED3);
   STM_EVAL_LEDInit(LED4);
   STM_EVAL_LEDInit(LED5);
   STM_EVAL_LEDInit(LED6);

   /* Turn on LEDs */
   STM_EVAL_LEDOn(LED3);
   STM_EVAL_LEDOn(LED4);
   STM_EVAL_LEDOn(LED5);
   STM_EVAL_LEDOn(LED6);

   // (STM32) UART <--> (PC) RS232
   uartInit(9600);
}

int main(int ac, char** av)
{
  const char * av_override[] = { "exe", "-v" }; //turn on verbose mode

  //System initialization
  systemInit();

  //Configure I/Os
  ioInit();

  //return CommandLineTestRunner::RunAllTests(ac, av);
  return CommandLineTestRunner::RunAllTests(2, av_override);
}

/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
extern "C" void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
extern "C" uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
