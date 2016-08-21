#######################################################
# Makefile for QT program
# Created by zhiyb @ GT-Soft
#

MOCH = prog.h form.h hexbyte.h
OBJS = main.o prog.o form.o hexbyte.o
TARG = QtAVR

CC = g++
MOC = /root/qt/qt-2.3.10/bin/moc
STRIP = strip
QTDIR = /root/qt/qt-2.3.10

COPT = -I$(QTDIR)/include -pipe -DQWS -fno-exceptions -fno-rtti -Wall -Wsign-compare -W -DNO_DEBUG
BOPT = -L$(QTDIR)/lib -Wl,-rpath,/opt/qt-2.3.10.new/lib -lqte

MOCC = $(addprefix moc_,$(subst .h,.cpp,$(MOCH)))
OBJS += $(subst .cpp,.o,$(MOCC))

all: $(TARG)

main.o: form.h hexbyte.h prog.h
form.o: form.h hexbyte.h prog.h
prog.o: prog.h
hexbyte.o: hexbyte.h

$(TARG): $(OBJS)
	$(CC) $(BOPT) -o $(TARG) $(OBJS)
	$(STRIP) $(TARG)

$(OBJS): %.o: %.cpp
	$(CC) -c $(COPT) $<

$(MOCC): moc_%.cpp: %.h
	$(MOC) -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(MOCC)

run: $(TARG)
	./$(TARG)
