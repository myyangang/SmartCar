################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/sdk/Core/core_riscv.c 

OBJS += \
./sdk/Core/core_riscv.o 

C_DEPS += \
./sdk/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Core/core_riscv.o: E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/sdk/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\Libraries\doc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Core" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Ld" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Peripheral" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Startup" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\project\user\inc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_common" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_device" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

