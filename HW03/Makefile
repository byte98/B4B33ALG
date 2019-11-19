CFLAGS+=-Wall
COMPILER=clang

program: hw03.o node.o plane.o hw03utils.o
	$(COMPILER) $(CFLAGS) -o program obj/hw03.o obj/node.o obj/plane.o obj/hw03utils.o

hw03.o: obj hw03.c
	$(COMPILER) $(CFLAGS) -c -o obj/hw03.o hw03.c

node.o: node.h node.c
	$(COMPILER) $(CFLAGS) -c -o obj/node.o node.c

plane.o: plane.h plane.c
	$(COMPILER) $(CFLAGS) -c -o obj/plane.o plane.c

hw03utils.o : hw03utils.h hw03utils.c
	$(COMPILER) $(CFLAGS) -c -o obj/hw03utils.o hw03utils.c

obj:
	mkdir obj

clean:
	$(RM) -r ./obj
	$(RM) ./program
	$(RM) ./hw03.tar.bz2

zip: hw03.tar.bz2
	@echo ""

hw03.tar.bz2: hw03.tar
	bzip2 hw03.tar

hw03.tar:
	tar -cvf hw03.tar ./*.c ./*.h