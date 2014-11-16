############################
# Makefile for C programs  #
# Author: zhiyb (Yubo Zhi) #
############################

FILE = min_max.c
TARG = min_max
ARGV = 

CC = gcc
GDB = gdb
STRIP = \#strip

COPT = -g -Wall -Wsign-compare
LOPT = 

OBJS = $(subst .c,.o,$(FILE))

$(TARG): $(OBJS)
	$(CC) $(LOPT) -o $(TARG) $(OBJS)
	$(STRIP) $(TARG)

$(OBJS): %.o: %.c
	$(CC) $(COPT) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: delete
delete:
	rm -f $(TARG) $(OBJS)

run: $(TARG)
	./$(TARG) $(ARGV)

gdb: $(TARG)
	$(GDB) ./$(TARG)

