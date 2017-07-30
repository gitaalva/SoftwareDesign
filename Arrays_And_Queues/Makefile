#############################################################################
#
#  makefile for AQueue-test
#
#############################################################################
#
#  If you move this makefile, update the variable below
#  or else depend won't work.
#
#############################################################################

MAKEFILE	= Makefile
CC		= g++
CFILES		= LQueue-test.cpp LQueue.cpp AQueue.cpp Array.cpp
HFILES		= LQueue.h AQueue.h Array.h
LOFILES		= LQueue-test.o LQueue.o
AOFILES		= AQueue-test.o AQueue.o Array.o

#############################################################################
# Flags for Installation
#############################################################################
BINDIR		= .
#############################################################################

DFLAGS		= -g
IFLAGS          = 
OPTFLAGS	=  # Enable this flag if compiler supports templates...
LDFLAGS		=  
CFLAGS		= $(IFLAGS) $(OPTFLAGS) $(DFLAGS)

#############################################################################
# G++ directives
#############################################################################
.SUFFIXES: .cpp
.cpp.o:
	$(CC) $(CFLAGS) -c $<
#############################################################################

all: LQueue-test AQueue-test

LQueue-test: $(LOFILES)
	$(CC) $(LDFLAGS) $(LOFILES) -o $@

AQueue-test: $(AOFILES)
	$(CC) $(LDFLAGS) $(AOFILES) -o $@

clean:
	/bin/rm -f *.o *.out *~ core

realclean: clean
	/bin/rm -rf LQueue-test AQueue-test

depend:
	g++dep -f $(MAKEFILE) $(CFILES)

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

Array.o: Array.cpp Array.h Array.inl
LQueue.o : LQueue.cpp LQueue.h
AQueue.o : AQueue.cpp AQueue.h
LQueue-test.o : LQueue-test.cpp LQueue.h LQueue.cpp
AQueue-test.o : AQueue-test.cpp AQueue.h AQueue.cpp Array.cpp Array.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
