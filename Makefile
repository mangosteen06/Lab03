# Makefile
all: testbst

testbst: testbst.o intbst.o
	g++ testbst.o intbst.o -o testbst

testbst.o: testbst.cpp intbst.o
	g++ -c testbst.cpp

intbst.o: intbst.cpp
	g++ -c intbst.cpp

clean:
	rm -f *.o

# Used: https://www.youtube.com/watch?v=_r7i5X0rXJk - "How to Create a Simple Makefile - Introduction to Makefiles" by Paul Programming