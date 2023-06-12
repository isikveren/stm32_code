################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/OLED/OLED.c 

OBJS += \
./hardware/OLED/OLED.o 

C_DEPS += \
./hardware/OLED/OLED.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/OLED/%.o: ../hardware/OLED/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\嵌入式代码\ch32v307\小车\Debug" -I"D:\嵌入式代码\ch32v307\小车\User\system" -I"D:\嵌入式代码\ch32v307\小车\hardware\LED" -I"D:\嵌入式代码\ch32v307\小车\hardware\OLED" -I"D:\嵌入式代码\ch32v307\小车\Core" -I"D:\嵌入式代码\ch32v307\小车\User" -I"D:\嵌入式代码\ch32v307\小车\Peripheral\inc" -I"D:\嵌入式代码\ch32v307\小车\hardware" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

