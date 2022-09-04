######################################################
# Variables  : edit this section accordingly

DEVICE = attiny84
F_CPU = 1000000
OUT = main
SRC = main.c
COM =COM4
AVR_BASE_PATH ="D:\ENGINEERING\Fubet tech\avr-gcc-8.5.0-1-x64-windows"
AVRDUDE_BASE_PATH = "D:\ENGINEERING\Fubet tech\avrdude"
OPTIMIZATION = -Og

######################################################

INC = -I$(AVR_BASE_PATH)/avr/include
CFLAGS = $(OPTIMIZATION) $(INC) -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) -Wall
LDFLAGS = -mmcu=$(DEVICE)
CC = $(AVR_BASE_PATH)/bin/avr-gcc
OBJCPY = $(AVR_BASE_PATH)/bin/avr-objcopy
SIZE = $(AVR_BASE_PATH)/bin/avr-size
AVRDUDE = $(AVRDUDE_BASE_PATH)/bin/avrdude
AVRDUDE_CONFIG = $(AVRDUDE_BASE_PATH)/etc/avrdude.conf
REMOVE = delete
PROGRAMMER = arduino
AVRDUDE_FLAGS = -b 19200
######################################################

OBJS = $(SRC:.c=.o)
.phony: all
all: $(OUT).hex

%.hex: %.elf
	$(OBJCPY) -O ihex $< $@
	$(SIZE) $(OUT).hex

%.elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.phony: clean
clean:
	$(REMOVE) *.hex *.elf *.o

.phony: flash
flash: $(OUT).hex
	$(AVRDUDE) -C $(AVRDUDE_CONFIG) -p $(DEVICE) -P $(COM) -c $(PROGRAMMER) $(AVRDUDE_FLAGS) -v  -U flash:w:$<
