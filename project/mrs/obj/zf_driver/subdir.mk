################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_adc.c \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_delay.c \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_dvp.c \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_encoder.c \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_flash.c \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_gpio.c \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_pit.c \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_pwm.c \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_soft_iic.c \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_spi.c \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_timer.c \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_uart.c \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_usb_cdc.c 

S_UPPER_SRCS += \
C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_irq.S 

OBJS += \
./zf_driver/zf_driver_adc.o \
./zf_driver/zf_driver_delay.o \
./zf_driver/zf_driver_dvp.o \
./zf_driver/zf_driver_encoder.o \
./zf_driver/zf_driver_flash.o \
./zf_driver/zf_driver_gpio.o \
./zf_driver/zf_driver_irq.o \
./zf_driver/zf_driver_pit.o \
./zf_driver/zf_driver_pwm.o \
./zf_driver/zf_driver_soft_iic.o \
./zf_driver/zf_driver_spi.o \
./zf_driver/zf_driver_timer.o \
./zf_driver/zf_driver_uart.o \
./zf_driver/zf_driver_usb_cdc.o 

S_UPPER_DEPS += \
./zf_driver/zf_driver_irq.d 

C_DEPS += \
./zf_driver/zf_driver_adc.d \
./zf_driver/zf_driver_delay.d \
./zf_driver/zf_driver_dvp.d \
./zf_driver/zf_driver_encoder.d \
./zf_driver/zf_driver_flash.d \
./zf_driver/zf_driver_gpio.d \
./zf_driver/zf_driver_pit.d \
./zf_driver/zf_driver_pwm.d \
./zf_driver/zf_driver_soft_iic.d \
./zf_driver/zf_driver_spi.d \
./zf_driver/zf_driver_timer.d \
./zf_driver/zf_driver_uart.d \
./zf_driver/zf_driver_usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
zf_driver/zf_driver_adc.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_delay.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_delay.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_dvp.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_encoder.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_flash.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_gpio.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_irq.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_irq.S
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pit.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_pit.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pwm.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_pwm.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_iic.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_soft_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_spi.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_timer.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_timer.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_uart.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_usb_cdc.o: C:/Users/Yaner/Desktop/SmartCar/libraries/zf_driver/zf_driver_usb_cdc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\SmartCar\Libraries\doc" -I"C:\Users\Yaner\Desktop\SmartCar\project\code" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\SmartCar\project\user\inc" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_common" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_device" -I"C:\Users\Yaner\Desktop\SmartCar\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

