# Modified by zhiyb (Yubo Zhi)

TRG	= simulator
SRC	= main.cpp
SUBDIRS	= tft-cpp common
INCDIRS	= .

PRGER		= usbasp
MCU_TARGET	= atmega644p
MCU_FREQ	= 12000000

TFT_HARDWARE	= ili9341_parallel
# (Experimental) Multiple font support
TFT_FONTS	= y

LIBS	+= -lm

EFUSE	= 0xFF
HFUSE	= 0x9C
LFUSE	= 0xE7

include ../../Makefile_AVR.defs
