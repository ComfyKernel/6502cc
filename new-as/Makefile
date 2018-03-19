CC=g++
CFLAGS=-std=c++17 -D__P_VER_MAJOR=1 -D__P_VER_MINOR=0

FILES=$(shell find -type f -name "*.cpp")
OBJS =$(patsubst %.cpp, %.o, $(FILES))

BIN  =../bin/6502-as-new

all: $(BIN)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CC) $(cFLAGS) $(OBJS) -o $(BIN)

clean:
	rm $(OBJS)
	rm $(BIN)
