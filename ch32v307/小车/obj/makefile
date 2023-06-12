################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include hardware/OLED/subdir.mk
-include hardware/LED/subdir.mk
-include hardware/subdir.mk
-include User/system/subdir.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
v307xiaoche.hex \

SECONDARY_LIST += \
v307xiaoche.lst \

SECONDARY_SIZE += \
v307xiaoche.siz \


# 所有目标
all: v307xiaoche.elf secondary-outputs

# 工具调用
v307xiaoche.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "D:\嵌入式代码\ch32v307\小车\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"v307xiaoche.map" --specs=nano.specs --specs=nosys.specs -o "v307xiaoche.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
v307xiaoche.hex: v307xiaoche.elf
	@	riscv-none-embed-objcopy -O ihex "v307xiaoche.elf"  "v307xiaoche.hex"
	@	@
v307xiaoche.lst: v307xiaoche.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "v307xiaoche.elf" > "v307xiaoche.lst"
	@	@
v307xiaoche.siz: v307xiaoche.elf
	@	riscv-none-embed-size --format=berkeley "v307xiaoche.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) v307xiaoche.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
