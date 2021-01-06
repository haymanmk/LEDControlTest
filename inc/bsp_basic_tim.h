/*
 * This head file defines the parameters to configure the basic timer, TIM6/7.
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f767xx.h"
#include "stm32_hal_legacy.h"
#include "stm32f7xx_hal.h"

/* Defines -------------------------------------------------------------------*/
#define BASIC_TIM				TIM6
#define BASIC_TIM_CLK_ENABLE()	__TIM6_CLK_ENABLE()

#define BASIC_TIM_IRQ			TIM6_DAC_IRQn

/* define private constants --------------------------------------------------*/
#define __COUNT_PERIOD			5000

/* Exported variables --------------------------------------------------------*/
TIM_HandleTypeDef TIM_TimeBaseStruct;

/* Private function ----------------------------------------------------------*/
static void TIMx_NVIC_Config(void);
static void TIM_Mode_Config(void);

/* Exported function ---------------------------------------------------------*/
void TIMx_Config(void);
