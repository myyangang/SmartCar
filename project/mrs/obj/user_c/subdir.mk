################################################################################
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Yaner/Desktop/camera/project/user/src/SEEKFREE_18TFT.c \
C:/Users/Yaner/Desktop/camera/project/user/src/isr.c \
C:/Users/Yaner/Desktop/camera/project/user/src/main.c 

OBJS += \
./user_c/SEEKFREE_18TFT.o \
./user_c/isr.o \
./user_c/main.o 

C_DEPS += \
./user_c/SEEKFREE_18TFT.d \
./user_c/isr.d \
./user_c/main.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/SEEKFREE_18TFT.o: C:/Users/Yaner/Desktop/camera/project/user/src/SEEKFREE_18TFT.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/isr.o: C:/Users/Yaner/Desktop/camera/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: C:/Users/Yaner/Desktop/camera/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Yaner\Desktop\camera\Libraries\doc" -I"C:\Users\Yaner\Desktop\camera\project\mrs\code" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Core" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Ld" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Peripheral" -I"C:\Users\Yaner\Desktop\camera\libraries\sdk\Startup" -I"C:\Users\Yaner\Desktop\camera\project\user\inc" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_common" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_device" -I"C:\Users\Yaner\Desktop\camera\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

