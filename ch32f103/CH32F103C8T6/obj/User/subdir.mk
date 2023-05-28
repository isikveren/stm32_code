################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Main.c \
../User/ch32f10x_it.c \
../User/system_ch32f10x.c 

OBJS += \
./User/Main.o \
./User/ch32f10x_it.o \
./User/system_ch32f10x.o 

C_DEPS += \
./User/Main.d \
./User/ch32f10x_it.d \
./User/system_ch32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mthumb-interwork -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"D:\stm32_code\ch32f103\CH32F103C8T6\Core" -I"D:\stm32_code\ch32f103\CH32F103C8T6\Debug" -I"D:\stm32_code\ch32f103\CH32F103C8T6\Peripheral\inc" -I"D:\stm32_code\ch32f103\CH32F103C8T6\Peripheral\src" -I"D:\stm32_code\ch32f103\CH32F103C8T6\User" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

