################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/pidkl25cpp.cpp \
../source/rpm_detect.cpp \
../source/servo_driver.cpp 

C_SRCS += \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/mtb.o \
./source/pidkl25cpp.o \
./source/rpm_detect.o \
./source/semihost_hardfault.o \
./source/servo_driver.o 

CPP_DEPS += \
./source/pidkl25cpp.d \
./source/rpm_detect.d \
./source/servo_driver.d 

C_DEPS += \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSDK_DEBUGCONSOLE=0 -DCPU_MKL25Z128VFM4 -DCPU_MKL25Z128VFM4_cm0plus -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../freertos -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSDK_DEBUGCONSOLE=0 -DCPU_MKL25Z128VFM4 -DCPU_MKL25Z128VFM4_cm0plus -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../freertos -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


