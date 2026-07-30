################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MonoGFX/MonoGFX.c 

OBJS += \
./MonoGFX/MonoGFX.o 

C_DEPS += \
./MonoGFX/MonoGFX.d 


# Each subdirectory must supply rules for building sources it contributes
MonoGFX/%.o: ../MonoGFX/%.c MonoGFX/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I../Core/Inc -I../Drivers/CMSIS -I../MonoGFX -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

