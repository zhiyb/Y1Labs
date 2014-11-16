############################
# Makefile for C programs  #
# Author: zhiyb (Yubo Zhi) #
############################

FILE = main.c copy.c
TARG = copy
ARGV = 

CC = gcc
STRIP = strip

COPT = -Wall -Wsign-compare
LOPT = 

OBJS = $(subst .c,.o,$(FILE))
RMSG = -e "\e[30;107m****** RUN HERE ******\e[0m"

all: $(TARG)

main.o: copy.h

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
	@echo $(RMSG)
	./$(TARG) $(ARGV)

