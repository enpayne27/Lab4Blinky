In today's lab we learned a lot about the STM32 Discovery board. The IDE we used
was the System Workbench through Eclipse. Besides learning the basic processes 
of the board, this lab offered a lot of insight into the functionality of the 
board's clock cycles and LED configurations.

Tips for programming the STM board:
Go into the Project Explorer and right click
    Clean project>Build Project>Target>Program chip
Then click the black reset button on the board and your most recent code should run.

The following is the final code I used for the repeated 1 second blink:

```
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
  while (1)
  {
uint32_t CurrentTicks = HAL_GetTick();
if ((CurrentTicks-PrevTicks)>= 1000){
PrevTicks = CurrentTicks;
BSP_LED_Toggle(LED2);
}
  }
}
```


The following is the final code I used for the SOS blink:

```
static void SystemClock_Config(void);
int main(void)
{
	HAL_Init();
	/* Configure the System clock to have a frequency of 80 MHz */
	SystemClock_Config();
	/* Configure the User LED */
	BSP_LED_Init(LED2);
	BSP_LED_On(LED2);
	int i = 0;
	int signal[18] = {1,0,1,0,1,0,2,0,2,0,2,0,1,0,1,0,1,0};
	/* Infinite loop */
	while(1){
		int cur = signal[i];
		uint32_t PrevTicks = HAL_GetTick();
		uint32_t CurrentTicks = HAL_GetTick();
		switch(cur){
			  /*space*/
			  case 0:
				  /*LED off for 1 second*/
				  BSP_LED_On(LED2);
				  while((CurrentTicks-PrevTicks)<=1000){
					CurrentTicks = HAL_GetTick();
				  }
			  break;
			  /*dot*/
			  case 1:
				  /*LED on for 1 second*/
				  BSP_LED_On(LED2);
				  while ((CurrentTicks-PrevTicks)<=1000){
					CurrentTicks = HAL_GetTick();
				  }
			  break;
			  /*dash*/
			  case 2:
				  /*LED on for 3 seconds*/
				  BSP_LED_On(LED2);
				  while ((CurrentTicks-PrevTicks)<=3000){
					CurrentTicks = HAL_GetTick();
				  }
			  break;
		  }i++;
	}
}
```
