############################
# Makefile for C programs  #
# Author: zhiyb (Yubo Zhi) #
############################

FILE = main.c
TARG = strtok
ARGV = 

CC = gcc
STRIP = strip

COPT = -Wall -Wsign-compare
LOPT = 

OBJS = $(subst .c,.o,$(FILE))
RMSG = -e "\033[30;107m****** RUN HERE ******\033[0m"

all: $(TARG)

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

