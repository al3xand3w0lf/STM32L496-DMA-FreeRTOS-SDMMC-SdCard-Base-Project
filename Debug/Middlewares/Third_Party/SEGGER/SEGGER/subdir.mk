################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT.c \
../Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT_printf.c \
../Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW.c \
../Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW_Config_FreeRTOS.c \
../Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW_FreeRTOS.c 

S_UPPER_SRCS += \
../Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT.o \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT_printf.o \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW.o \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW_Config_FreeRTOS.o \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW_FreeRTOS.o 

S_UPPER_DEPS += \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT.d \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT_printf.d \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW.d \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW_Config_FreeRTOS.d \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/SEGGER/SEGGER/%.o Middlewares/Third_Party/SEGGER/SEGGER/%.su: ../Middlewares/Third_Party/SEGGER/SEGGER/%.c Middlewares/Third_Party/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L496xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/SEGGER/SEGGER/Config -I../Middlewares/Third_Party/SEGGER/SEGGER -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/SEGGER/SEGGER/%.o: ../Middlewares/Third_Party/SEGGER/SEGGER/%.S Middlewares/Third_Party/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"D:/Documents/PROJECTS/101 HELIOS/3 Programmieren STM32/Firmware/HELIOS_STM32/Middlewares/Third_Party/SEGGER/SEGGER" -I"D:/Documents/PROJECTS/101 HELIOS/3 Programmieren STM32/Firmware/HELIOS_STM32/Middlewares/Third_Party/SEGGER/SEGGER/Config" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-SEGGER

clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-SEGGER:
	-$(RM) ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT.d ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT.o ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT.su ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT_printf.d ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT_printf.o ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT_printf.su ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW.d ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW.o ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW.su ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW_Config_FreeRTOS.d ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW_Config_FreeRTOS.o ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW_Config_FreeRTOS.su ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW_FreeRTOS.d ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW_FreeRTOS.o ./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW_FreeRTOS.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-SEGGER

