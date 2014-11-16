###############################
# Makefile for AVR C programs #
# Author: zhiyb (Yubo Zhi)    #
###############################

# Generic
FILE := main.c
TARG := 7SEG.hex
MCU := atmega644p
FREQ := 12000000
PROG := usbasp

# Fuse
EFUSE := 0xFF
HFUSE := 0x9C
LFUSE := 0xE7
FDIR := fuse
EFILE := fuse/e.txt
HFILE := fuse/h.txt
LFILE := fuse/l.txt

# EEPROM
EFILE := eeprom.bin

# Build
CC := avr-gcc
OBJC := avr-objcopy
SIZE := avr-size
DOWN := avrdude
FUSE := avrdude

COPT := -mmcu=$(MCU) -DF_CPU=$(FREQ) -Wall -Os
OOPT := -O ihex
DOPT := -U flash:w:$(TARG)
FWRITE := -q -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m
FREAD := -q -U lfuse:r:$(LFILE):h -U hfuse:r:$(HFILE):h -U efuse:r:$(EFILE):h
EREAD := -U eeprom:r:$(EFILE):r
EWRITE := -U eeprom:w:$(EFILE):r

OBJS := $(subst .c,.o,$(FILE))
DMSG := -e "\033[30;107m****** DOWNLOAD HERE ******\033[0m"

all: $(TARG)

$(TARG): $(OBJS)
	$(OBJC) $(OOPT) $(OBJS) $(TARG)
	$(SIZE) $(TARG)

$(OBJS): %.o: %.c
	$(CC) $(COPT) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: delete
delete:
	rm -f $(TARG) $(OBJS)

flash: $(TARG)
	@echo $(DMSG)
	$(DOWN) -c $(PROG) -p $(MCU) $(DOPT)

.PHONY: readfuse
readfuse:
	mkdir -p $(FDIR)
	$(DOWN) -c $(PROG) -p $(MCU) $(FREAD)

.PHONY: fuse
fuse:
	$(DOWN) -c $(PROG) -p $(MCU) $(FWRITE)

.PHONY: readeeprom
readeeprom:
	$(DOWN) -c $(PROG) -p $(MCU) $(EREAD)

.PHONY: eeprom
eeprom:
	$(DOWN) -c $(PROG) -p $(MCU) $(EWRITE)
