#####################	MakeFile	###########################
CC=gcc
CXX=g++
CFLAGS=-lm

easy-uncertainty: main.cpp calculator.o
	$(CXX) -o $@ $< $(CFLAGS)

mystack.o:mystack.cpp
	$(CXX) -c $< $(CFLAGS)

uncertainty.o:uncertainty.cpp
	$(CXX) -c $< $(CFLAGS)

calculator.o:calculator.cpp mystack.o uncertainty.o
	$(CXX) -c $< $(CFLAGS)
clean:
	rm -rf *.o easy-uncertainty

##############################################################
