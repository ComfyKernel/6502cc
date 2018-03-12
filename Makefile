all: bin-as

bin-as:
	make -C as/

clean-as:
	rm as/main.o
	rm bin/6502-as
