#########################################
# Makefile for single file multi target #
# Author: zhiyb (Yubo Zhi)              #
#########################################

FILE = arr_func.c double.c

CC = gcc
STRIP = strip

COPT = -Wall -Wsign-compare
LOPT = 

OBJS = $(subst .c,,$(FILE))
RMSG = -e "\e[30;107m****** RUN HERE ******\e[0m"

.PHONY: all
all: $(OBJS)

$(OBJS): %: %.c
	$(CC) $(COPT) $(LOPT) -o $@ $<
	$(STRIP) $@

.PHONY: clean
clean:
	rm -f $(OBJS)

run: $(TARG)
	@echo $(RMSG)
	./$(TARG) $(ARGV)

