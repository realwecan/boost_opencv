################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../HOGfeatures.cpp \
../boost.cpp \
../cascadeclassifier.cpp \
../features.cpp \
../haarfeatures.cpp \
../imagestorage.cpp \
../lbpfeatures.cpp \
../traincascade.cpp 

OBJS += \
./HOGfeatures.o \
./boost.o \
./cascadeclassifier.o \
./features.o \
./haarfeatures.o \
./imagestorage.o \
./lbpfeatures.o \
./traincascade.o 

CPP_DEPS += \
./HOGfeatures.d \
./boost.d \
./cascadeclassifier.d \
./features.d \
./haarfeatures.d \
./imagestorage.d \
./lbpfeatures.d \
./traincascade.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/opencv -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


