#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sun Nov  9 12:57:11 2014
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak


CFLAGS = -Wall -Wextra -pedantic -std=c99 -ggdb
LFLAGS = -ggdb
LDFLAGS =


########## End of flags from header.mak


CPP_FILES =	
C_FILES =	amigonet.c amigosim.c bst.c friends.c
PS_FILES =	
S_FILES =	
H_FILES =	amigonet.h bst.h friends.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	amigonet.o bst.o friends.o 

#
# Main targets
#

all:	amigosim 

amigosim:	amigosim.o $(OBJFILES)
	$(CC) $(CFLAGS) -o amigosim amigosim.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

amigonet.o:	amigonet.h bst.h friends.h
amigosim.o:	amigonet.h
bst.o:	amigonet.h bst.h friends.h
friends.o:	amigonet.h friends.h

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
