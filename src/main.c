/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "main.h"

/* Macros */
#define LED_YELLOW		BSP_LED_On(LED_GREEN);\
						BSP_LED_On(LED_RED)

#define LED_ALL			BSP_LED_On(LED_GREEN);\
						BSP_LED_On(LED_BLUE);\
						BSP_LED_On(LED_RED)

#define LED_TOGGLE		BSP_LED_Toggle(LED_GREEN);\
						BSP_LED_Toggle(LED_BLUE);\
						BSP_LED_Toggle(LED_RED)

/* Private variables ---------------------------------------------------------*/
uint16_t TimesButtonPressed;
uint32_t NumbSysTick;
/* Define the variables and macros for B1 USER button mounted on the board. */
#define B1_USER_INT_GPIO_PORT			GPIOC

/* Private functions ---------------------------------------------------------*/
static void SystemClock_Config(void);
static void EXTI_Key_Config(void);
static void SysTick_Init(void);
static void Delay_10us(__IO uint32_t NumbTimes);

int main(void)
{
	HAL_Init();

	/* Configure the system clock to 216 MHz */
	SystemClock_Config();

	/* Initialize the LEDs mounted on STM32F767ZI-Nucleo_144 board */
	BSP_LED_Init(LED_GREEN);
	BSP_LED_Init(LED_BLUE);
	BSP_LED_Init(LED_RED);


	LED_ALL;

	/* Initialize the system timer for the utility of making applications such as time delay. */
	SysTick_Init();

	/* Configure the EXTI function for USER Button B1.
	 * And the function call for the interrupt event is defined in the function named HAL_GPIO_EXTI_Callback
	 * in this source file.
	 */
	//EXTI_Key_Config();

	/* Configure and enable the general purpose timer, TIM6. */
	TIMx_Config();

	for(;;)
	{
		//Delay_10us(60000);

		//LED_TOGGLE;
	}
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            PLL_R                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */

static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;
	//HAL_StatusTypeDef ret = HAL_OK;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 432;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9;
	RCC_OscInitStruct.PLL.PLLR = 7;

	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		while(1) {};
	}

	/* Activate the OverDrive to reach the 216 Mhz Frequency */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		while(1) {};
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	   clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK |
								   RCC_CLOCKTYPE_HCLK |
								   RCC_CLOCKTYPE_PCLK1 |
								   RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
	{
		while(1) {};
	}
}

/**
 * @brief	Initialize the EXTI configuration for GPIO port.
 * 		  	Here we use the B1 USER button mounted on the board
 * 		  	as the source to trigger the IRQ of EXTI.
 * 		  	And we use it to toggle the status of the USER LED1, 2, and 3
 * 		  	every time when the button is pressed.
 * 		  	B1  USER button is connected to GPIO pin, PC13.
 * @param	None
 * @retval	None
 */
void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* Enable the clock for USER Button connected to GPIO pin PC13.	 */
	USER_BUTTON_GPIO_CLK_ENABLE();

	/* Configure GPIO pin PC13 as input with External Interrupt */
	GPIO_InitStruct.Pin = USER_BUTTON_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(USER_BUTTON_GPIO_PORT, &GPIO_InitStruct);

	/* Enable and set Button EXTI Interrupt to the lowest priority */
	HAL_NVIC_SetPriority(USER_BUTTON_EXTI_IRQn, 0x0F, 0x00);
	HAL_NVIC_EnableIRQ(USER_BUTTON_EXTI_IRQn);

}

/**
 * @brief	A callback function handles the IRQ request triggered by the EXTI15_10.
 * @para	GPIO_Pin: specify the pin connected to EXTI line.
 * @retval	None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	BSP_LED_GetState(3);
	if (GPIO_Pin == USER_BUTTON_PIN){
		TimesButtonPressed++;
		switch (TimesButtonPressed)
		{
		case 1:
			BSP_LED_Toggle(LED_GREEN);
			break;
		case 2:
			BSP_LED_Toggle(LED_BLUE);
			break;
		case 3:
			BSP_LED_Toggle(LED_RED);
			TimesButtonPressed = 0;
			break;
		}
	}
}

/**
 * @brief	Initialize the system timer which is also called SysTick
 * 			to generate interrupt requests on a regular basis.
 * @param	None
 * @retval	None
 */
static void SysTick_Init(void)
{
	/* SystemFrequency / 1000		An interrupt request happens every 1000us
	 * SystemFrequency / 100000		An interrupt request happens every 10us
	 * SystemFrequency / 1000000	An interrupt request happens every 1us
	 */
	if (HAL_SYSTICK_Config(SystemCoreClock / 100000))
	{
		/* Capture error */
		while (1);
	}
}

/**
 * @brief	hold the process here till the NumbTimes counts down to zero
 * 			to make a delay.
 * @param	NumbTimes: the time delay can be calculated by multiplying NumbTimes by 10us.
 * @retval	None
 */
static void Delay_10us(__IO uint32_t NumbTimes)
{
	NumbSysTick = NumbTimes;

	while (NumbSysTick != 0);
}

/**
  * @brief  SYSTICK callback.
  * @retval None
  */
void HAL_SYSTICK_Callback(void)
{
	if (NumbSysTick != 0x00UL) NumbSysTick--;
}

/**
 * @brief	TIM Update interrupt callback
 * @param	htim: a structure for handlers of TIM.
 * @retval	None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == (&TIM_TimeBaseStruct))
	{
		LED_TOGGLE;
	}
}
