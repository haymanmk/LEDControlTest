################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL_Driver/Src/Legacy/stm32f7xx_hal_can.c 

OBJS += \
./HAL_Driver/Src/Legacy/stm32f7xx_hal_can.o 

C_DEPS += \
./HAL_Driver/Src/Legacy/stm32f7xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
HAL_Driver/Src/Legacy/%.o: ../HAL_Driver/Src/Legacy/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -DSTM32 -DSTM32F7 -DSTM32F767ZITx -DNUCLEO_F767ZI -DDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -I"D:/Ac6/workspace/LEDControlTest/HAL_Driver/Inc/Legacy" -I"D:/Ac6/workspace/LEDControlTest/Utilities/STM32F7xx_Nucleo_144" -I"D:/Ac6/workspace/LEDControlTest/inc" -I"D:/Ac6/workspace/LEDControlTest/CMSIS/device" -I"D:/Ac6/workspace/LEDControlTest/CMSIS/core" -I"D:/Ac6/workspace/LEDControlTest/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


