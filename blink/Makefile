# Put your source files here (*.c)
SRCS=src/main.c src/system_stm32f10x.c src/syscalls.c
SRCS +=startup/startup_stm32f10x_md.s
#
# Binaries will be generated with this name (.elf, .bin, .hex)
PROJ_NAME=blink

# Compiler settings. Only edit CFLAGS to include other header files.
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

# Compiler flags
CFLAGS  = -g -O2 -Wall -TSTM32F103XX_FLASH.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3
CFLAGS += -Iinclude
CFLAGS += -I"/home/widar/STMTOOLS/libs/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/"
CFLAGS += -I"/home/widar/STMTOOLS/libs/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/inc"

# add startup file to build
#.PHONY: proj

# Commands
all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	rm -f *.o $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin

# Flash the STM32F4
#burn: proj
#$(STLINK)/st-flash write $(PROJ_NAME).bin 0x8000000
