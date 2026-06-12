#currently makefile crashes without manual creation of ./obj/Drivers/ include this somehow
CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m3 -g -mthumb -std=gnu11 -Iinclude/CMSIS/Device/ST/STM32F1xx/Include/ -Iinclude/CMSIS/Include/ -Isrc/Drivers/
LFLAGS = -nostdlib -T 
LINKER = stm32f103scrtch.ld
OUTPUT = run

SRC=./src
OBJ=./obj
DRIVER=$(SRC)/Drivers
DRIVER_OBJ=./obj/Drivers

SRCS=$(wildcard $(SRC)/*.c)
SRC_OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

DRIVERS=$(wildcard $(DRIVER)/*.c)
DRIVER_OBJS=$(patsubst $(DRIVER)/%.c, $(DRIVER_OBJ)/%.o, $(DRIVERS))

$(OUTPUT): $(SRC_OBJS) $(DRIVER_OBJS)
	$(CC) $(LFLAGS) $(LINKER) -g -Wl,-Map=$(OBJ)/debug.map $(SRC_OBJS) $(DRIVER_OBJS) -o $(OUTPUT).elf 

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(DRIVER_OBJ)/%.o: $(DRIVER)/%.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ)/*.o ./*.elf $(OBJ)/*.map $(DRIVER_OBJ)/*.o
flash:
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg
