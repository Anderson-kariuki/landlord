################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/user_libs/src/i2c_lcd.c \
../Core/user_libs/src/user_systick.c 

OBJS += \
./Core/user_libs/src/i2c_lcd.o \
./Core/user_libs/src/user_systick.o 

C_DEPS += \
./Core/user_libs/src/i2c_lcd.d \
./Core/user_libs/src/user_systick.d 


# Each subdirectory must supply rules for building sources it contributes
Core/user_libs/src/%.o Core/user_libs/src/%.su Core/user_libs/src/%.cyclo: ../Core/user_libs/src/%.c Core/user_libs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/andyn/STM32CubeIDE/workspace_1.12.1/landlord/Core/user_libs/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-user_libs-2f-src

clean-Core-2f-user_libs-2f-src:
	-$(RM) ./Core/user_libs/src/i2c_lcd.cyclo ./Core/user_libs/src/i2c_lcd.d ./Core/user_libs/src/i2c_lcd.o ./Core/user_libs/src/i2c_lcd.su ./Core/user_libs/src/user_systick.cyclo ./Core/user_libs/src/user_systick.d ./Core/user_libs/src/user_systick.o ./Core/user_libs/src/user_systick.su

.PHONY: clean-Core-2f-user_libs-2f-src

