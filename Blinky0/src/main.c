/*Lab4Blinky Project*/
/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l475e_iot01.h"
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
int main(void)
{
  HAL_Init();
  /* Configure the System clock to have a frequency of 80 MHz */
  SystemClock_Config();
  /* Configure the User LED */
  BSP_LED_Init(LED2);
  BSP_LED_Off(LED2);
  /* Infinite loop */
  uint32_t PrevTicks = HAL_GetTick();
  uint32_t CurrentTicks = HAL_GetTick();
  int signal[36] = {1,0,1,0,1,0,2,0,2,0,2,0,1,0,1,0,1,0};
  int cur = 0;

  switch(cur){
  	  /*space*/
  	  case 0:
  		  /*LED on for 1 second*/
  		  while((CurrentTicks-PrevTicks)<= 1000){
  			CurrentTicks = HAL_GetTick();
  		  }BSP_LED_Off(LED2);
	  break;
	  /*dot*/
  	  case 1:
  		  /*LED on for 1 seconds*/
  		  while ((CurrentTicks-PrevTicks)<= 1000){
  			CurrentTicks = HAL_GetTick();
  		  }BSP_LED_On(LED2);
	  break;
	  /*dash*/
  	  case 2:
  		  /*LED off for 3 second*/
  		  while ((CurrentTicks-PrevTicks)<=3000){
  			CurrentTicks = HAL_GetTick();
  		  }BSP_LED_On(LED2);
	  break;
	  }
  while(1){
	  CurrentTicks = HAL_GetTick();
	  PrevTicks = CurrentTicks;
	  for(int i = 0; i < 18; i++) {
		  cur = signal[i];
		  PrevTicks = CurrentTicks;
		  CurrentTicks = HAL_GetTick();
	  }
  }
}
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (MSI)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            MSI Frequency(Hz)              = 4000000
  *            PLL_M                          = 1
  *            PLL_N                          = 40
  *            PLL_R                          = 2
  *            PLL_P                          = 7
  *            PLL_Q                          = 4
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  /* MSI is enabled after System reset, activate PLL with MSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}
