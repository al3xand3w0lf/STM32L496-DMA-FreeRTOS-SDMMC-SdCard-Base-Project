################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_RTT.c \
../Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_RTT_printf.c \
../Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_SYSVIEW.c 

OBJS += \
./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_RTT.o \
./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_RTT_printf.o \
./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_SYSVIEW.o 

C_DEPS += \
./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_RTT.d \
./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_RTT_printf.d \
./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_SYSVIEW.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/SEGGER/SEGGER_Src/%.o Middlewares/Third_Party/SEGGER/SEGGER_Src/%.su: ../Middlewares/Third_Party/SEGGER/SEGGER_Src/%.c Middlewares/Third_Party/SEGGER/SEGGER_Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L496xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/SEGGER/SEGGER_Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-SEGGER_Src

clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-SEGGER_Src:
	-$(RM) ./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_RTT.d ./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_RTT.o ./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_RTT.su ./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_RTT_printf.d ./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_RTT_printf.o ./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_RTT_printf.su ./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_SYSVIEW.d ./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_SYSVIEW.o ./Middlewares/Third_Party/SEGGER/SEGGER_Src/SEGGER_SYSVIEW.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-SEGGER_Src

