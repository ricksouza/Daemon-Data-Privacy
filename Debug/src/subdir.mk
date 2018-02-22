################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/client.c \
../src/client2.c \
../src/common.c \
../src/func_IBE.c \
../src/func_aux_file.c \
../src/func_cryptographic.c \
../src/func_retrieve.c \
../src/func_secret_share.c \
../src/func_send.c \
../src/main.c \
../src/server.c 

OBJS += \
./src/client.o \
./src/client2.o \
./src/common.o \
./src/func_IBE.o \
./src/func_aux_file.o \
./src/func_cryptographic.o \
./src/func_retrieve.o \
./src/func_secret_share.o \
./src/func_send.o \
./src/main.o \
./src/server.o 

C_DEPS += \
./src/client.d \
./src/client2.d \
./src/common.d \
./src/func_IBE.d \
./src/func_aux_file.d \
./src/func_cryptographic.d \
./src/func_retrieve.d \
./src/func_secret_share.d \
./src/func_send.d \
./src/main.d \
./src/server.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"/home/rick/Dropbox/workspace_C/Daemon_Data_Privacy/include" -I"/home/rick/Dropbox/workspace_C/secretsharer" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


