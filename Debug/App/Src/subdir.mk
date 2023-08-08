################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Src/application.c 

OBJS += \
./App/Src/application.o 

C_DEPS += \
./App/Src/application.d 


# Each subdirectory must supply rules for building sources it contributes
App/Src/%.o App/Src/%.su: ../App/Src/%.c App/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Otavi/Documents/Embed/STM32/Projects/DataPacket/Misc/Inc" -I"C:/Users/Otavi/Documents/Embed/STM32/Projects/DataPacket/App/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Src

clean-App-2f-Src:
	-$(RM) ./App/Src/application.d ./App/Src/application.o ./App/Src/application.su

.PHONY: clean-App-2f-Src

