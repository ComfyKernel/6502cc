VERSION_MAJOR=0
VERSION_MINOR=4

CC      = g++
CFLAGS  = -std=c++11 -Wall -Wextra -O2 -D__V_MAJOR__=$(VERSION_MAJOR)\
			 	       -D__V_MINOR__=$(VERSION_MINOR)

FILES   = $(shell find -name "*.cpp" -type f)
OBJECTS = $(patsubst %.cpp, %.o, $(FILES))

OUT = ../bin/6502-as

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(OUT)

%.o: %.cpp
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm $(OBJECTS)
