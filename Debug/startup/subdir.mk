################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f767xx.s 

OBJS += \
./startup/startup_stm32f767xx.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -I"D:/Ac6/workspace/LEDControlTest/HAL_Driver/Inc/Legacy" -I"D:/Ac6/workspace/LEDControlTest/Utilities/STM32F7xx_Nucleo_144" -I"D:/Ac6/workspace/LEDControlTest/inc" -I"D:/Ac6/workspace/LEDControlTest/CMSIS/device" -I"D:/Ac6/workspace/LEDControlTest/CMSIS/core" -I"D:/Ac6/workspace/LEDControlTest/HAL_Driver/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


