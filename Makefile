#####################	MakeFile	###########################
CC=gcc
CXX=g++
CFLAGS=-lm

easy-uncertainty: main.cpp uncertainty.cpp mystack.cpp
	$(CXX) -o $@ $< $(CFLAGS)

debug:main.cpp uncertainty.cpp mystack.cpp
	$(CXX) -o $@ $< $(CFLAGS) -g
clean:
	rm -rf *.o easy-uncertainty

##############################################################
