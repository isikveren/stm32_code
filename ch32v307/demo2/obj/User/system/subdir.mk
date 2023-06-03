################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/system/system.c 

OBJS += \
./User/system/system.o 

C_DEPS += \
./User/system/system.d 


# Each subdirectory must supply rules for building sources it contributes
User/system/%.o: ../User/system/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\stm32_code\ch32v307\demo2\Debug" -I"D:\stm32_code\ch32v307\demo2\User\system" -I"D:\stm32_code\ch32v307\demo2\hardware\LED" -I"D:\stm32_code\ch32v307\demo2\hardware\OLED" -I"D:\stm32_code\ch32v307\demo2\Core" -I"D:\stm32_code\ch32v307\demo2\User" -I"D:\stm32_code\ch32v307\demo2\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

