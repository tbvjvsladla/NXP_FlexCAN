################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"C:/NXP/S32DS_Power_v2017.R1/S32DS/S32_SDK_S32PA_RTM_3.0.0/platform/drivers/src/pit/pit_driver.c" \
"C:/NXP/S32DS_Power_v2017.R1/S32DS/S32_SDK_S32PA_RTM_3.0.0/platform/drivers/src/pit/pit_hw_access.c" \

C_SRCS += \
C:/NXP/S32DS_Power_v2017.R1/S32DS/S32_SDK_S32PA_RTM_3.0.0/platform/drivers/src/pit/pit_driver.c \
C:/NXP/S32DS_Power_v2017.R1/S32DS/S32_SDK_S32PA_RTM_3.0.0/platform/drivers/src/pit/pit_hw_access.c \

OBJS_OS_FORMAT += \
./SDK/platform/drivers/src/pit/pit_driver.o \
./SDK/platform/drivers/src/pit/pit_hw_access.o \

C_DEPS_QUOTED += \
"./SDK/platform/drivers/src/pit/pit_driver.d" \
"./SDK/platform/drivers/src/pit/pit_hw_access.d" \

OBJS += \
./SDK/platform/drivers/src/pit/pit_driver.o \
./SDK/platform/drivers/src/pit/pit_hw_access.o \

OBJS_QUOTED += \
"./SDK/platform/drivers/src/pit/pit_driver.o" \
"./SDK/platform/drivers/src/pit/pit_hw_access.o" \

C_DEPS += \
./SDK/platform/drivers/src/pit/pit_driver.d \
./SDK/platform/drivers/src/pit/pit_hw_access.d \


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/drivers/src/pit/pit_driver.o: C:/NXP/S32DS_Power_v2017.R1/S32DS/S32_SDK_S32PA_RTM_3.0.0/platform/drivers/src/pit/pit_driver.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@SDK/platform/drivers/src/pit/pit_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "SDK/platform/drivers/src/pit/pit_driver.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/platform/drivers/src/pit/pit_hw_access.o: C:/NXP/S32DS_Power_v2017.R1/S32DS/S32_SDK_S32PA_RTM_3.0.0/platform/drivers/src/pit/pit_hw_access.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@SDK/platform/drivers/src/pit/pit_hw_access.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "SDK/platform/drivers/src/pit/pit_hw_access.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


