################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/zf_common/zf_common_clock.c \
E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/zf_common/zf_common_debug.c \
E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/zf_common/zf_common_fifo.c \
E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/zf_common/zf_common_font.c \
E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/zf_common/zf_common_function.c \
E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/zf_common/zf_common_interrupt.c 

OBJS += \
./zf_common/zf_common_clock.o \
./zf_common/zf_common_debug.o \
./zf_common/zf_common_fifo.o \
./zf_common/zf_common_font.o \
./zf_common/zf_common_function.o \
./zf_common/zf_common_interrupt.o 

C_DEPS += \
./zf_common/zf_common_clock.d \
./zf_common/zf_common_debug.d \
./zf_common/zf_common_fifo.d \
./zf_common/zf_common_font.d \
./zf_common/zf_common_function.d \
./zf_common/zf_common_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
zf_common/zf_common_clock.o: E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\Libraries\doc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Core" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Ld" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Peripheral" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Startup" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\project\user\inc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_common" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_device" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o: E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\Libraries\doc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Core" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Ld" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Peripheral" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Startup" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\project\user\inc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_common" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_device" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o: E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\Libraries\doc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Core" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Ld" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Peripheral" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Startup" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\project\user\inc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_common" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_device" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o: E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\Libraries\doc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Core" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Ld" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Peripheral" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Startup" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\project\user\inc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_common" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_device" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o: E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\Libraries\doc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Core" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Ld" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Peripheral" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Startup" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\project\user\inc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_common" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_device" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o: E:/soft-hard-reference/CH32V307/all_program/head\ before\ competition/head(2022-6-26BugOver)/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\Libraries\doc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Core" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Ld" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Peripheral" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\sdk\Startup" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\project\user\inc" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_common" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_device" -I"E:\soft-hard-reference\CH32V307\all_program\head before competition\head(2022-6-26BugOver)\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

