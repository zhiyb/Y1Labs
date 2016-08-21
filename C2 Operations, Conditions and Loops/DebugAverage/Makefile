############################
# Makefile for C programs  #
# Author: zhiyb (Yubo Zhi) #
############################

FILE = average.c
TARG = average
ARGV = 

CC = gcc
STRIP = strip

COPT = -Wall -Wsign-compare
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

