#########################################
# Makefile for single file multi target #
# Author: zhiyb (Yubo Zhi)              #
#########################################

FILE = loopnest.c addtable.c

CC = gcc
STRIP = strip

COPT = -Wall -Wsign-compare
LOPT = 

OBJS = $(subst .c,,$(FILE))

.PHONY: all
all: $(OBJS)

$(OBJS): %: %.c
	$(CC) $(COPT) $(LOPT) -o $@ $<
	$(STRIP) $@

.PHONY: clean
clean:
	rm -f $(OBJS)

run: $(TARG)
	./$(TARG) $(ARGV)

