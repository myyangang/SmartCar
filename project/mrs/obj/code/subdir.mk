################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/motor.c \
../code/pid.c \
../code/servo.c \
../code/uart.c 

OBJS += \
./code/motor.o \
./code/pid.o \
./code/servo.o \
./code/uart.o 

C_DEPS += \
./code/motor.d \
./code/pid.d \
./code/servo.d \
./code/uart.d 


# Each subdirectory must supply rules for building sources it contributes
code/%.o: ../code/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

