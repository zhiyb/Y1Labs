###############################
# Makefile for AVR C programs #
# Author: zhiyb (Yubo Zhi)    #
###############################

FILE := 
TARG := atmega644pa-12mhz_2048.hex
MCU := atmega644p
FREQ := 12000000
PROG := c232hm

EFUSE := 0xFF
HFUSE := 0x9C
LFUSE := 0xE7
FDIR := fuse
EFILE := fuse/e.txt
HFILE := fuse/h.txt
LFILE := fuse/l.txt

CC := avr-gcc
OBJC := avr-objcopy
DOWN := avrdude
FUSE := avrdude

COPT := -mmcu=$(MCU) -DF_CPU=$(FREQ) -Wall -Os
OOPT := -O ihex
DOPT := -c $(PROG) -p $(MCU) -q -U flash:w:$(TARG)
FWRITE := -c $(PROG) -p $(MCU) -q -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m
FREAD := -c $(PROG) -p $(MCU) -q -U lfuse:r:$(LFILE):h -U hfuse:r:$(HFILE):h -U efuse:r:$(EFILE):h

OBJS := $(subst .c,.o,$(FILE))
DMSG := -e "\033[30;107m****** DOWNLOAD HERE ******\033[0m"

all: $(TARG)

$(TARG): $(OBJS)
	$(OBJC) $(OOPT) $(OBJS) $(TARG)

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
	$(DOWN) $(DOPT)

.PHONY: readfuse
readfuse:
	mkdir -p $(FDIR)
	$(FUSE) $(FREAD)

.PHONY: fuse
fuse:
	$(FUSE) $(FWRITE)
