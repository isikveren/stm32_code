################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/LED/LED.c 

OBJS += \
./hardware/LED/LED.o 

C_DEPS += \
./hardware/LED/LED.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/LED/%.o: ../hardware/LED/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\Ƕ��ʽ����\ch32v307\demo2\Debug" -I"D:\Ƕ��ʽ����\ch32v307\demo2\User\system" -I"D:\Ƕ��ʽ����\ch32v307\demo2\hardware\LED" -I"D:\Ƕ��ʽ����\ch32v307\demo2\hardware\OLED" -I"D:\Ƕ��ʽ����\ch32v307\demo2\Core" -I"D:\Ƕ��ʽ����\ch32v307\demo2\User" -I"D:\Ƕ��ʽ����\ch32v307\demo2\Peripheral\inc" -I"D:\Ƕ��ʽ����\ch32v307\demo2\hardware" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

