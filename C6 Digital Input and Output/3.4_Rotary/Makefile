# http://www.nongnu.org/avr-libc/user-manual/group__demo__project.html
# Modified by zhiyb (Yubo Zhi)

PRG	= 7SEG
OBJ	= main.o
MCU_TARGET	= atmega644p
OPTIMIZE	= -Os

DEFS	= -DF_CPU=12000000
LIBS	=

PRGER	= usbasp

EFUSE	= 0xFF
HFUSE	= 0x9C
LFUSE	= 0xE7

# You should not have to change anything below here.

CC	= avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS	= -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
override LDFLAGS	= -Wl,-Map,$(PRG).map

OBJCOPY	= avr-objcopy
OBJDUMP	= avr-objdump
SIZE	= avr-size

all: $(PRG).elf lst text eeprom

$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(SIZE) $@

# dependency:
# (Ignored - but may cause error)

clean:
	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

lst: $(PRG).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

# Only hex is needed; Others: bin, srec
text: hex

hex: $(PRG).hex
bin: $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images

# Only ehex is needed; Others: ebin, esrec
eeprom:	ehex

ehex: $(PRG)_eeprom.hex
ebin: $(PRG)_eeprom.bin
esrec: $(PRG)_eeprom.srec

%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@
#	|| { echo empty $@ not generated; exit 0; }

%_eeprom.srec: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@
#	|| { echo empty $@ not generated; exit 0; }

%_eeprom.bin: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@
#	|| { echo empty $@ not generated; exit 0; }

# For program MCU with avrdude.

AVRDUDE	= avrdude

flash: hex
	$(AVRDUDE) -c $(PRGER) -p $(MCU_TARGET) -U flash:w:$(PRG).hex

eep: ehex
	$(AVRDUDE) -c $(PRGER) -p $(MCU_TARGET) -U eeprom:w:$(PRG)_eeprom.hex

fuse:
	$(AVRDUDE) -c $(PRGER) -p $(MCU_TARGET) -U efuse:w:$(EFUSE):m \
		-U hfuse:w:$(HFUSE):m -U lfuse:w:$(LFUSE):m

# Every thing below here is used by avr-libc's build system and can be ignored
# by the casual user.

FIG2DEV	= fig2dev
EXTRA_CLEAN_FILES	= *.hex *.bin *.srec

dox: eps png pdf

eps: $(PRG).eps
png: $(PRG).png
pdf: $(PRG).pdf

%.eps: %.fig
	$(FIG2DEV) -L eps $< $@

%.pdf: %.fig
	$(FIG2DEV) -L pdf $< $@

%.png: %.fig
	$(FIG2DEV) -L png $< $@
