################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# �Զ����ɵ��ļ�����Ҫ�༭��
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
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\Ƕ��ʽ����\ch32v307\С��\Debug" -I"D:\Ƕ��ʽ����\ch32v307\С��\User\system" -I"D:\Ƕ��ʽ����\ch32v307\С��\hardware\LED" -I"D:\Ƕ��ʽ����\ch32v307\С��\hardware\OLED" -I"D:\Ƕ��ʽ����\ch32v307\С��\Core" -I"D:\Ƕ��ʽ����\ch32v307\С��\User" -I"D:\Ƕ��ʽ����\ch32v307\С��\Peripheral\inc" -I"D:\Ƕ��ʽ����\ch32v307\С��\hardware" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

