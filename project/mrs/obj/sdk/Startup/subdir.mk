################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Yaner/Desktop/SmartCar/libraries/sdk/Startup/system_ch32v30x.c 

S_UPPER_SRCS += \
C:/Users/Yaner/Desktop/SmartCar/libraries/sdk/Startup/startup_ch32v30x.S 

OBJS += \
./sdk/Startup/startup_ch32v30x.o \
./sdk/Startup/system_ch32v30x.o 

S_UPPER_DEPS += \
./sdk/Startup/startup_ch32v30x.d 

C_DEPS += \
./sdk/Startup/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Startup/startup_ch32v30x.o: C:/Users/Yaner/Desktop/SmartCar/libraries/sdk/Startup/startup_ch32v30x.S
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Startup/system_ch32v30x.o: C:/Users/Yaner/Desktop/SmartCar/libraries/sdk/Startup/system_ch32v30x.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

