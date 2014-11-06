CC = gcc

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c

CFLAGS = -Wall -Wextra -pedantic -std=c99 -ggdb
LFLAGS = -ggdb
LDFLAGS =

C_FILES =	amigonet.c amigosim.c
H_FILES =	amigonet.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	amigonet.o 

all:	amigosim 

amigosim:	amigosim.o $(OBJFILES)
	$(CC) $(CFLAGS) -o amigosim amigosim.o $(OBJFILES) $(CLIBFLAGS)

amigonet.o:	amigonet.h
amigosim.o:	amigonet.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) amigosim.o core

realclean:        clean
	-/bin/rm -f amigosim 
