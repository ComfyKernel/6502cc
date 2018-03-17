all: bin-as

bin-as:
	make -C as/

clean-as:
	rm as/main.o
	rm bin/6502-as

new-bin-as:
	make -C new-as/

clean-new-as:
	rm $(wildcard new-as/*.o)
	rm bin/6502-new-as
