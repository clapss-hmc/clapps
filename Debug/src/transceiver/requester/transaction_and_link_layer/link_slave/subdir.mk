################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/transceiver/requester/transaction_and_link_layer/link_slave/reoder_responser.cpp 

OBJS += \
./src/transceiver/requester/transaction_and_link_layer/link_slave/reoder_responser.o 

CPP_DEPS += \
./src/transceiver/requester/transaction_and_link_layer/link_slave/reoder_responser.d 


# Each subdirectory must supply rules for building sources it contributes
src/transceiver/requester/transaction_and_link_layer/link_slave/%.o: ../src/transceiver/requester/transaction_and_link_layer/link_slave/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/systemc-2.3.1/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


