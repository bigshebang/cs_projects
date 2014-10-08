CC = gcc
RM = rm -f

CFLAGS = -Wall -std=c99 -pedantic -Wextra
C_FILES =	matrix.c scanner.c tokenize.c
H_FILES =	classes.h matrix.h scanner.h
SOURCEFILES =	$(H_FILES) $(C_FILES)
OBJFILES =	matrix.o scanner.o 

# Main targets

all:	tokenize 

tokenize:	tokenize.o $(OBJFILES)
	$(CC) $(CFLAGS) -o tokenize tokenize.o $(OBJFILES) $(CLIBFLAGS)

# Dependencies
matrix.o:	classes.h matrix.h
scanner.o:	classes.h scanner.h
tokenize.o:	classes.h matrix.h scanner.h

# Housekeeping

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) tokenize.o core

realclean:        clean
	-/bin/rm -f tokenize 
