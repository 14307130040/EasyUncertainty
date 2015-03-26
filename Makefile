#####################	MakeFile	###########################
CC=gcc
CXX=g++
CFLAGS=

easy-uncertainty: main.o
	$(CXX) -o $@ $< $(CFLAGS)

stack.o:MyStack.h
	$(CXX) -c $< $(CFLAGS)

clean:
	rm -rf *.o easy-uncertainty
##############################################################
