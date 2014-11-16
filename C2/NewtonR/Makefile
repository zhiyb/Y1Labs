############################
# Makefile for C programs  #
# Author: zhiyb (Yubo Zhi) #
############################

FILE = main.c
TARG = NewtonR
ARGV = 

CC = gcc
STRIP = strip

COPT = -Wall -Wsign-compare
LOPT = -lm

OBJS = $(subst .c,.o,$(FILE))

$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LOPT)
	$(STRIP) $(TARG)

$(OBJS): %.o: %.c
	$(CC) -c -o $@ $< $(COPT)

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: delete
delete:
	rm -f $(TARG) $(OBJS)

run: $(TARG)
	./$(TARG) $(ARGV)

