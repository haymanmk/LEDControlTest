/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "bsp_basic_tim.h"

#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
#include "stm32f7xx_it.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles SysTick Handler, but only if no RTOS defines it.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif
}

/**
 * @brief	This function handles EXTI15_10 external interrupt.
 * @param	None
 * @retval	None
 */
void EXTI15_10_IRQHandler(void)
{
	/* configure a callback function to handle the IRQ request,
	 * and this callback function should be put in the project such as main.c.
	 */
	HAL_GPIO_EXTI_IRQHandler(USER_BUTTON_PIN);
}

/**
 * @brief	This function handles TIM6 interrupt.
 * @param	None
 * @retval	None
 */
void TIM6_DAC_IRQHandler(void)
{
	/* Enable the callback function depending on the flag in the TIM6/7 status register, TIMxSR, which is set by hardware.
	 * For TIM6/7, the only available status bit is UIF which is set as 1 when an overflow occurs.
	 * In this context, the callback function, HAL_TIM_PeriodElapsedCallback, will be enabled.
	 */
	HAL_TIM_IRQHandler(&TIM_TimeBaseStruct);
}
