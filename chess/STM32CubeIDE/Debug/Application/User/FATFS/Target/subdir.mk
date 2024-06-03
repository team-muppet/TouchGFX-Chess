################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Repos/ams-project-2/chess/FATFS/Target/bsp_driver_sd.c \
C:/Repos/ams-project-2/chess/FATFS/Target/fatfs_platform.c \
C:/Repos/ams-project-2/chess/FATFS/Target/sd_diskio.c 

C_DEPS += \
./Application/User/FATFS/Target/bsp_driver_sd.d \
./Application/User/FATFS/Target/fatfs_platform.d \
./Application/User/FATFS/Target/sd_diskio.d 

OBJS += \
./Application/User/FATFS/Target/bsp_driver_sd.o \
./Application/User/FATFS/Target/fatfs_platform.o \
./Application/User/FATFS/Target/sd_diskio.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/FATFS/Target/bsp_driver_sd.o: C:/Repos/ams-project-2/chess/FATFS/Target/bsp_driver_sd.c Application/User/FATFS/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DSTM32H7B3xxQ -DDEBUG -DUSE_BPP=24 -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP -I../../TouchGFX/target -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../TouchGFX/target/generated -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/Components/Common -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/BSP/STM32H7B3I-DK -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/BSP/Components/mx25lm51245g -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Utilities/JPEG -I../../Middlewares/Third_Party/LibJPEG/include -I../../FATFS/Target -I../../FATFS/App -I../../Middlewares/Third_Party/FatFs/src -I"../../Middlewares/Third_Party/rapidjson" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/FATFS/Target/fatfs_platform.o: C:/Repos/ams-project-2/chess/FATFS/Target/fatfs_platform.c Application/User/FATFS/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DSTM32H7B3xxQ -DDEBUG -DUSE_BPP=24 -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP -I../../TouchGFX/target -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../TouchGFX/target/generated -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/Components/Common -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/BSP/STM32H7B3I-DK -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/BSP/Components/mx25lm51245g -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Utilities/JPEG -I../../Middlewares/Third_Party/LibJPEG/include -I../../FATFS/Target -I../../FATFS/App -I../../Middlewares/Third_Party/FatFs/src -I"../../Middlewares/Third_Party/rapidjson" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/FATFS/Target/sd_diskio.o: C:/Repos/ams-project-2/chess/FATFS/Target/sd_diskio.c Application/User/FATFS/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DSTM32H7B3xxQ -DDEBUG -DUSE_BPP=24 -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP -I../../TouchGFX/target -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../TouchGFX/target/generated -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/Components/Common -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/BSP/STM32H7B3I-DK -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/BSP/Components/mx25lm51245g -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Utilities/JPEG -I../../Middlewares/Third_Party/LibJPEG/include -I../../FATFS/Target -I../../FATFS/App -I../../Middlewares/Third_Party/FatFs/src -I"../../Middlewares/Third_Party/rapidjson" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-FATFS-2f-Target

clean-Application-2f-User-2f-FATFS-2f-Target:
	-$(RM) ./Application/User/FATFS/Target/bsp_driver_sd.cyclo ./Application/User/FATFS/Target/bsp_driver_sd.d ./Application/User/FATFS/Target/bsp_driver_sd.o ./Application/User/FATFS/Target/bsp_driver_sd.su ./Application/User/FATFS/Target/fatfs_platform.cyclo ./Application/User/FATFS/Target/fatfs_platform.d ./Application/User/FATFS/Target/fatfs_platform.o ./Application/User/FATFS/Target/fatfs_platform.su ./Application/User/FATFS/Target/sd_diskio.cyclo ./Application/User/FATFS/Target/sd_diskio.d ./Application/User/FATFS/Target/sd_diskio.o ./Application/User/FATFS/Target/sd_diskio.su

.PHONY: clean-Application-2f-User-2f-FATFS-2f-Target

