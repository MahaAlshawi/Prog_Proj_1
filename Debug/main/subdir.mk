################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main/Prog_Proj_1.c 

OBJS += \
./main/Prog_Proj_1.o 

C_DEPS += \
./main/Prog_Proj_1.d 


# Each subdirectory must supply rules for building sources it contributes
main/%.o: ../main/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


