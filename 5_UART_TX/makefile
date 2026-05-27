CC = arm-none-eabi-gcc
SRCS = main.c stm32f103_startscrtch.c
OUTPUT = run
CFLAGS = -mcpu=cortex-m3 -mthumb -std=gnu11 -IChip_Headers/CMSIS/Device/ST/STM32F1xx/Include/ -IChip_Headers/CMSIS/Include/ -IChip_Headers/inc/
LFLAGS = -nostdlib -T 
LINKER = stm32f103scrtch.ld

OBJS = $(SRCS:.c=.o)

#the output depends on the .o files existing 
$(OUTPUT): $(OBJS)
	$(CC) $(LFLAGS) $(LINKER) -Wl,-Map=debug.map $(OBJS) -o $(OUTPUT).elf 

#in order for the .o files to exist the .c files are used
# ^ is target @ in dependencies
%.o:%.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o *.elf
flash:
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg
