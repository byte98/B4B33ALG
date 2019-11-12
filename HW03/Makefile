CFLAGS+=-Wall
COMPILER=clang

program: hw03.o node.o
	$(COMPILER) $(CFLAGS) -o program obj/hw03.o obj/node.o

hw03.o: obj hw03.c
	$(COMPILER) $(CFLAGS) -c -o obj/hw03.o hw03.c

node.o: node.h node.c
	$(COMPILER) $(CFLAGS) -c -o obj/node.o node.c

obj:
	mkdir obj

clean:
	$(RM) -r ./obj
	$(RM) ./program
