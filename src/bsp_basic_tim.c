/*
 * This source file defines the function to configure the basic timer, TIM6/7.
 */

/* Includes ------------------------------------------------------------------*/
#include "bsp_basic_tim.h"

/* Private functions ---------------------------------------------------------*/
/**
 * @brief	Configure the NVIC for the time-base unit such as priority and IRQ handler.
 * @param	None
 * @retval	None
 */
static void TIMx_NVIC_Config(void)
{
	/* set the preemption priority and subpriority.
	 * According to the default setting here, the priority group 4 is selected.
	 * All the 4 bits is used for preemption priority, and the subpriority is no longer available.
	 */
	HAL_NVIC_SetPriority(BASIC_TIM_IRQ, 0x03, 0x00);

	/* Enable the IRQ request */
	HAL_NVIC_EnableIRQ(BASIC_TIM_IRQ);
}

/**
 * @brief	Configure the source clock for the basic timer.
 * @param	None
 * @retval	None
 */
static void TIM_Mode_Config(void)
{
	/* Enable the clock for the basic timer. */
	BASIC_TIM_CLK_ENABLE();

	/* Configure the necessary parameters */
	TIM_TimeBaseStruct.Instance = BASIC_TIM;

	/* Specify the period value to be loaded into the active Auto-reload register
	 * at next update event. And this count-up timer starts counting from 0x0000 and up to 0xFFFF.
	 */
	TIM_TimeBaseStruct.Init.Period = __COUNT_PERIOD - 1;

	/* Select a prescaler to make the counter clocked by the prescaler output CK_CNT,
	 * which is calculated with this formula
	 * 		Internal clock(CK_INT) / Prescaler(PSC) = CK_CNT
	 * Because TIM6/7 is connected to the bus APB1 the information can be found in the boundary address table
	 * in the reference manual. The TIMxCLK from RCC can be determined depending on the TIMPRE bit configuration
	 * in RCC_DCKCFGR. The TIMPRE bit used to be set as 0, so the frequency of TIMxCLK is twice of PCLK2.
	 * 		TIMxCLK = 2 * PCLK2
	 * 		=> PCLK2 = HCLK / 4(APB1 prescaler is defined in SystemClock_Config in main.c)
	 * 		=> TIMxCLK = HCLK / 2 = SystemCoreClock / 2 = 108MHz
	 * In order to get a 10000Hz timer, the TIM_Prescaler is expected to set as following manner.
	 * 		BasicTimerFrequency = TIMxCLK / (TIM_Prescaler + 1) = 10000Hz
	 */
	TIM_TimeBaseStruct.Init.Prescaler = 1080 - 1;

	/* Initialize the TIMx and launch a callback function, HAL_TIM_Base_MspInit. */
	HAL_TIM_Base_Init(&TIM_TimeBaseStruct);

	/* Start the TIM base generation in interrupt mode */
	HAL_TIM_Base_Start_IT(&TIM_TimeBaseStruct);
}

/**
 * @brief	Configure the NVIC and TIM.
 * @param	None
 * @retval	None
 */
void TIMx_Config(void)
{
	/* Configure the NVIC */
	TIMx_NVIC_Config();

	/* Configure the TIM */
	TIM_Mode_Config();
}
