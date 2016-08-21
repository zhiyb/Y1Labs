# http://www.nongnu.org/avr-libc/user-manual/group__demo__project.html
# Modified by zhiyb (Yubo Zhi) - For Qt

PRG	= HelloWorld
SRC	= main.cpp window.cpp
MOCH	= window.h
SUBDIRS = 
VERSION	= 0.0.1

CROSS	= 
OPTIMIZE	= -Os
STRIP	= true
DEFS	= -Wall -Werror
LIBS	= -lQtCore -lQtGui

QTDIR	= /usr/lib64/qt4
QTINC	= /usr/include/qt4 #$(QTDIR)/include
QTLIB	= /usr/lib/x86_64-linux-gnu #$(QTDIR)/lib64

# You should not have to change anything below here.

MOCC	= $(addprefix moc_,$(subst .h,.cpp,$(MOCH)))
OBJ	= $(subst .c,.o,$(subst .cpp,.o,$(SRC) $(MOCC)))

ifdef CROSS
PREFIX	= $(CROSS)-
else
PREFIX	=
endif
CC	= $(PREFIX)gcc
CPP	= $(PREFIX)g++
LD	= $(PREFIX)g++
STRIP	+= && $(PREFIX)strip
MOC	= /usr/lib64/qt4/bin/moc

CFLAGS	= -g -c $(DEFS) $(OPTIMIZE) -I$(QTINC)
LDFLAGS	= -g $(LIBS) -L$(QTLIB)

all: subdirs $(MOCC) $(PRG)

$(MOCC): moc_%.cpp: %.h
	$(MOC) -o $@ $<

$(PRG): $(OBJ)
	$(LD) -o $@ $^ $(LDFLAGS)
	$(STRIP) $@ || true

%.o: %.cpp
	$(CPP) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Subdirectories

.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

# Dependency:

-include $(OBJ:.o=.d)

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# Clean up

.PHONY: clean
clean:
	for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean); done
	rm -rf $(OBJ) $(MOCC) *.d *.d.* $(PRG) $(EXTRA_CLEAN_FILES)

# Publish: source code & hex target archive

TAR	= tar
TARFLAGS	= -jc
ARCHIVE	= $(PRG)-$(VERSION).tar.bz2
EXTRA_CLEAN_FILES	+= $(ARCHIVE)

.PHONY: archive
archive: $(ARCHIVE)

$(ARCHIVE): $(PRG)
	$(TAR) $(TARFLAGS) -f $(ARCHIVE) $(SRC) $(MOCH) *.h $(PRG) Makefile

# Run the program

.PHONY: run
run: $(PRG)
	./$(PRG)

# Debug, using gdb

.PHONY: debug
debug: $(PRG)
	gdb ./$(PRG)
