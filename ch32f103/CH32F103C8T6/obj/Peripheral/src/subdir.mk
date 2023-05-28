################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripheral/src/ch32f10x_adc.c \
../Peripheral/src/ch32f10x_bkp.c \
../Peripheral/src/ch32f10x_can.c \
../Peripheral/src/ch32f10x_crc.c \
../Peripheral/src/ch32f10x_dac.c \
../Peripheral/src/ch32f10x_dbgmcu.c \
../Peripheral/src/ch32f10x_dma.c \
../Peripheral/src/ch32f10x_exti.c \
../Peripheral/src/ch32f10x_flash.c \
../Peripheral/src/ch32f10x_gpio.c \
../Peripheral/src/ch32f10x_i2c.c \
../Peripheral/src/ch32f10x_iwdg.c \
../Peripheral/src/ch32f10x_misc.c \
../Peripheral/src/ch32f10x_pwr.c \
../Peripheral/src/ch32f10x_rcc.c \
../Peripheral/src/ch32f10x_rtc.c \
../Peripheral/src/ch32f10x_spi.c \
../Peripheral/src/ch32f10x_tim.c \
../Peripheral/src/ch32f10x_usart.c \
../Peripheral/src/ch32f10x_usb.c \
../Peripheral/src/ch32f10x_usb_host.c \
../Peripheral/src/ch32f10x_wwdg.c 

OBJS += \
./Peripheral/src/ch32f10x_adc.o \
./Peripheral/src/ch32f10x_bkp.o \
./Peripheral/src/ch32f10x_can.o \
./Peripheral/src/ch32f10x_crc.o \
./Peripheral/src/ch32f10x_dac.o \
./Peripheral/src/ch32f10x_dbgmcu.o \
./Peripheral/src/ch32f10x_dma.o \
./Peripheral/src/ch32f10x_exti.o \
./Peripheral/src/ch32f10x_flash.o \
./Peripheral/src/ch32f10x_gpio.o \
./Peripheral/src/ch32f10x_i2c.o \
./Peripheral/src/ch32f10x_iwdg.o \
./Peripheral/src/ch32f10x_misc.o \
./Peripheral/src/ch32f10x_pwr.o \
./Peripheral/src/ch32f10x_rcc.o \
./Peripheral/src/ch32f10x_rtc.o \
./Peripheral/src/ch32f10x_spi.o \
./Peripheral/src/ch32f10x_tim.o \
./Peripheral/src/ch32f10x_usart.o \
./Peripheral/src/ch32f10x_usb.o \
./Peripheral/src/ch32f10x_usb_host.o \
./Peripheral/src/ch32f10x_wwdg.o 

C_DEPS += \
./Peripheral/src/ch32f10x_adc.d \
./Peripheral/src/ch32f10x_bkp.d \
./Peripheral/src/ch32f10x_can.d \
./Peripheral/src/ch32f10x_crc.d \
./Peripheral/src/ch32f10x_dac.d \
./Peripheral/src/ch32f10x_dbgmcu.d \
./Peripheral/src/ch32f10x_dma.d \
./Peripheral/src/ch32f10x_exti.d \
./Peripheral/src/ch32f10x_flash.d \
./Peripheral/src/ch32f10x_gpio.d \
./Peripheral/src/ch32f10x_i2c.d \
./Peripheral/src/ch32f10x_iwdg.d \
./Peripheral/src/ch32f10x_misc.d \
./Peripheral/src/ch32f10x_pwr.d \
./Peripheral/src/ch32f10x_rcc.d \
./Peripheral/src/ch32f10x_rtc.d \
./Peripheral/src/ch32f10x_spi.d \
./Peripheral/src/ch32f10x_tim.d \
./Peripheral/src/ch32f10x_usart.d \
./Peripheral/src/ch32f10x_usb.d \
./Peripheral/src/ch32f10x_usb_host.d \
./Peripheral/src/ch32f10x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/%.o: ../Peripheral/src/%.c
	@	@	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mthumb-interwork -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"D:\stm32_code\ch32f103\CH32F103C8T6\Core" -I"D:\stm32_code\ch32f103\CH32F103C8T6\Debug" -I"D:\stm32_code\ch32f103\CH32F103C8T6\Peripheral\inc" -I"D:\stm32_code\ch32f103\CH32F103C8T6\Peripheral\src" -I"D:\stm32_code\ch32f103\CH32F103C8T6\User" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

