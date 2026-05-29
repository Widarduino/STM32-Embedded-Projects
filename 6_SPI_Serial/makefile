CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m3 -mthumb -std=gnu11 -Iinclude/CMSIS/Device/ST/STM32F1xx/Include/ -Iinclude/CMSIS/Include/ -Isrc/Drivers/
LFLAGS = -nostdlib -T 
LINKER = stm32f103scrtch.ld
OUTPUT = run

SRC=./src
SRCS=$(wildcard $(SRC)/*.c)
OBJ=./obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))


$(OUTPUT): $(OBJS)
	$(CC) $(LFLAGS) $(LINKER) -Wl,-Map=debug.map $(OBJS) -o $(OUTPUT).elf 

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ)/*.o ./*.elf ./*.map
flash:
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg
