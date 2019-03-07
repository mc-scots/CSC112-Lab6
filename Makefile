CXXFLAGS=`fltk-config --cxxflags`
LDFLAGS=`fltk-config --ldflags`
TARGETS=peg_test pegPuzzles
CC=g++
LD=g++

all: $(TARGETS)
pegPuzzles: pegPuzzles.o peg.o insanity.o
	g++ $(CFLAGS) -o $@ $^ $(LDFLAGS)
peg_test: peg_test.o peg.o
	g++ $(CFLAGS) -o $@ $^ $(LDFLAGS)
peg.o: peg.h peg.cpp
clean:
	rm -f $(TARGETS) *.o
