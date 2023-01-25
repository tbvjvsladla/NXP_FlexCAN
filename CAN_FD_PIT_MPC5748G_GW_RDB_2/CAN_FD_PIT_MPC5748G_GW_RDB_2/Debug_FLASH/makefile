################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 32
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Generated_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include SDK/platform/devices/MPC5748G/startup/subdir.mk
-include SDK/platform/devices/subdir.mk
-include SDK/platform/drivers/src/clock/MPC57xx/subdir.mk
-include SDK/platform/drivers/src/edma/subdir.mk
-include SDK/platform/drivers/src/flexcan/subdir.mk
-include SDK/platform/drivers/src/interrupt/subdir.mk
-include SDK/platform/drivers/src/pins/siul2/subdir.mk
-include SDK/platform/drivers/src/pit/subdir.mk
-include SDK/rtos/osif/subdir.mk
-include Sources/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
CAN_FD_PIT_MPC5748G_GW_RDB_2.elf \

EXECUTABLES_QUOTED += \
"CAN_FD_PIT_MPC5748G_GW_RDB_2.elf" \

EXECUTABLES_OS_FORMAT += \
CAN_FD_PIT_MPC5748G_GW_RDB_2.elf \

SECONDARY_SIZE += \
CAN_FD_PIT_MPC5748G_GW_RDB_2.siz \

SECONDARY_SIZE_QUOTED += \
"CAN_FD_PIT_MPC5748G_GW_RDB_2.siz" \

SECONDARY_SIZE_OS_FORMAT += \
CAN_FD_PIT_MPC5748G_GW_RDB_2.siz \


# All Target
all: warning-messages explicit-dependencies CAN_FD_PIT_MPC5748G_GW_RDB_2.elf secondary-outputs

# Tool invocations
CAN_FD_PIT_MPC5748G_GW_RDB_2.elf: $(OBJS) C:/NXP/S32DS_Power_v2017.R1/S32DS/S32_SDK_S32PA_RTM_3.0.0/platform/devices/MPC5748G/linker/gcc/MPC5748G_Z4_0/MPC5748G_flash.ld $(OSPT) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #33 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	powerpc-eabivle-gcc -o "CAN_FD_PIT_MPC5748G_GW_RDB_2.elf" "@CAN_FD_PIT_MPC5748G_GW_RDB_2.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED) $(OSPT)
	@echo 'Finished building target: $@'
	@echo ' '

CAN_FD_PIT_MPC5748G_GW_RDB_2.siz: $(EXECUTABLES)
	@echo 'Executing target #34 $@'
	@echo 'Invoking: Standard S32DS Print Size'
	powerpc-eabivle-size --format=berkeley $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*/*.d ./*/*/*/*.d ./*/*/*/*/*/*.d ./*/*/*/*/*/*/*.d  ./*/*.o ./*/*/*/*.o ./*/*/*/*/*/*.o ./*/*/*/*/*/*/*.o ./*/*/*.o  $(SECONDARY_SIZE_QUOTED) $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

