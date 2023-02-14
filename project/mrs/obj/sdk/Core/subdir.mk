################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Yaner/Desktop/SmartCar/libraries/sdk/Core/core_riscv.c 

OBJS += \
./sdk/Core/core_riscv.o 

C_DEPS += \
./sdk/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Core/core_riscv.o: C:/Users/Yaner/Desktop/SmartCar/libraries/sdk/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

