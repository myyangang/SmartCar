################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/sdk/Startup/system_ch32v30x.c 

S_UPPER_SRCS += \
E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/sdk/Startup/startup_ch32v30x.S 

OBJS += \
./sdk/Startup/startup_ch32v30x.o \
./sdk/Startup/system_ch32v30x.o 

S_UPPER_DEPS += \
./sdk/Startup/startup_ch32v30x.d 

C_DEPS += \
./sdk/Startup/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Startup/startup_ch32v30x.o: E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/sdk/Startup/startup_ch32v30x.S
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Startup" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_driver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Startup/system_ch32v30x.o: E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/sdk/Startup/system_ch32v30x.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\Libraries\doc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Core" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Ld" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Peripheral" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Startup" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\project\user\inc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_common" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_device" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

