CC=g++
CXXFLAGS=-g --std=c++11
WIDGET=term.o application.o keystream.o widget.o
TARGETS=pegPuzzles

all: $(TARGETS)
pegPuzzles: $(WIDGET) pegPuzzles.o peg.o insanity.o
peg.o: peg.h peg.cpp
clean:
	rm -f $(TARGETS) *.o

# $Revision: 1.1 $
#   $Log: Makefile,v $
#   Revision 1.1  2017/03/29 13:47:31  1ea49c2b19284e86b645075d033e28d0
#   Initial revision
#
