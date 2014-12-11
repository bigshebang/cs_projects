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
CFLAGS = -Wall -Wextra -pedantic -std=c99 -ggdb
CPP_FILES =	
C_FILES =	builtin.c external.c history.c mysh.c parse.c
PS_FILES =	
S_FILES =	
H_FILES =	builtin.h external.h history.h parse.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	builtin.o external.o history.o parse.o 

#
# Main targets
#

all:	mysh 

mysh:	mysh.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mysh mysh.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

builtin.o:	builtin.h history.h parse.h
external.o:	external.h
history.o:	history.h
mysh.o:	builtin.h external.h history.h parse.h
parse.o:	parse.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) mysh.o core

realclean:        clean
	-/bin/rm -f mysh 
