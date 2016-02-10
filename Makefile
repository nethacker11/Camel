
CC = gcc
CXX = g++

INCLUDES = 
CFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g 
LDLIBS = -framework SDL2 -framework SDL2_image 


camel: 



.PHONY: clean
clean:
	rm -rf *.o a.out camel *.dSYM 
