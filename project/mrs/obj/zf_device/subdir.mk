################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_absolute_encoder.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_bluetooth_ch9141.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_bluetooth_ch9141_ch2.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_camera.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_icm20602.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_ips114.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_ips200_parallel8.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_mpu6050.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_mt9v03x_dvp.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_oled.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_scc8660_dvp.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_tft180.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_type.c \
C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_wireless_uart.c 

OBJS += \
./zf_device/zf_device_absolute_encoder.o \
./zf_device/zf_device_bluetooth_ch9141.o \
./zf_device/zf_device_bluetooth_ch9141_ch2.o \
./zf_device/zf_device_camera.o \
./zf_device/zf_device_icm20602.o \
./zf_device/zf_device_ips114.o \
./zf_device/zf_device_ips200_parallel8.o \
./zf_device/zf_device_mpu6050.o \
./zf_device/zf_device_mt9v03x_dvp.o \
./zf_device/zf_device_oled.o \
./zf_device/zf_device_scc8660_dvp.o \
./zf_device/zf_device_tft180.o \
./zf_device/zf_device_type.o \
./zf_device/zf_device_wireless_uart.o 

C_DEPS += \
./zf_device/zf_device_absolute_encoder.d \
./zf_device/zf_device_bluetooth_ch9141.d \
./zf_device/zf_device_bluetooth_ch9141_ch2.d \
./zf_device/zf_device_camera.d \
./zf_device/zf_device_icm20602.d \
./zf_device/zf_device_ips114.d \
./zf_device/zf_device_ips200_parallel8.d \
./zf_device/zf_device_mpu6050.d \
./zf_device/zf_device_mt9v03x_dvp.d \
./zf_device/zf_device_oled.d \
./zf_device/zf_device_scc8660_dvp.d \
./zf_device/zf_device_tft180.d \
./zf_device/zf_device_type.d \
./zf_device/zf_device_wireless_uart.d 


# Each subdirectory must supply rules for building sources it contributes
zf_device/zf_device_absolute_encoder.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_absolute_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_bluetooth_ch9141.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_bluetooth_ch9141.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_bluetooth_ch9141_ch2.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_bluetooth_ch9141_ch2.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_camera.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_camera.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_icm20602.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_icm20602.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_ips114.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_ips114.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_ips200_parallel8.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_ips200_parallel8.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_mpu6050.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_mpu6050.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_mt9v03x_dvp.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_mt9v03x_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_oled.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_oled.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_scc8660_dvp.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_scc8660_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_tft180.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_tft180.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_type.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_type.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_wireless_uart.o: C:/Users/Yaner/Desktop/camera/libraries/zf_device/zf_device_wireless_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

