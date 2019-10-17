CFLAGS+=-Wall
OUTPUT=./program
COMPILER=clang

program: hw01utils.o hw01.o
	$(COMPILER) $(CFLAGS) -o $(OUTPUT) ./obj/hw01.o ./obj/hw01utils.o 

hw01utils.o: hw01utils.h obj
	$(COMPILER) $(CFLAGS) -c -o ./obj/hw01utils.o hw01utils.c

hw01.o: obj
	$(COMPILER) $(CFLAGS) -c -o ./obj/hw01.o hw01.c

obj:
	mkdir ./obj

run:
	$(OUTPUT)

clean:
	rm -r ./obj
	rm $(OUTPUT)

zip:
	@echo "Not implemented yet"