#############################################################################
#
#  makefile for adapter-test
#
#############################################################################
#
#  If you move this makefile, update the variable below
#  or else depend won't work.
#
#############################################################################

MAKEFILE	= Makefile
CC		= g++
TFILES		= LQueue.o STLQueue.o AQueue.o Array.o Queue.o adapter-test.o

#############################################################################
# Flags for Installation
#############################################################################
BINDIR		= .
#############################################################################

DFLAGS		= -ggdb
IFLAGS          = 
OPTFLAGS	=  # Enable this flag if compiler supports templates...
LDFLAGS		= -ggdb
CFLAGS		= $(IFLAGS) $(OPTFLAGS) $(DFLAGS)
ARRAYS      = ../Arrays_And_Queues/

#############################################################################
# G++ directives
#############################################################################
.SUFFIXES: .C .cpp
.cpp.o:
	$(CC) $(CFLAGS) -c $<
#############################################################################

all: adapter-test

adapter-test: $(TFILES)
	$(CC) $(LDFLAGS) $(TFILES) -o $@

clean:
	/bin/rm -f *.o *.out *~ core

realclean: clean
	/bin/rm -rf adapter-test

depend:
	g++dep -f $(MAKEFILE) $(CFILES)

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

Array.o: Array.cpp Array.h Array.inl
LQueue.o : LQueue.cpp LQueue.h
STLQueue.o : STLQueue.h
AQueue.o : AQueue.cpp AQueue.h
adapter-test.o : adapter-test.cpp Queue.h Queue.cpp AQueue.h AQueue.cpp LQueue.h LQueue.cpp STLQueue.cpp

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
