COMPILER=clang
CFLAGS+=-Wall

program: hw04.o consolecolor.o consolecolorutils.o queue.o hw04utils.o
	$(COMPILER) $(CFLAGS) -lm -o program obj/hw04.o obj/consolecolor.o obj/consolecolorutils.o obj/queue.o obj/hw04utils.o

hw04.o: obj hw04.c
	$(COMPILER) $(CFLAGS) -c -o obj/hw04.o hw04.c

obj:
	mkdir obj

consolecolor.o: obj ConsoleColor.c ConsoleColor.h
	$(COMPILER) $(CFLAGS) -c -o obj/consolecolor.o ConsoleColor.c

consolecolorutils.o: obj ConsoleColor_utils.c ConsoleColor_utils.h
	$(COMPILER) $(CFLAGS) -c -o obj/consolecolorutils.o ConsoleColor_utils.c

queue.o: obj queue.c queue.h
	$(COMPILER) $(CFLAGS) -c -o obj/queue.o queue.c

hw04utils.o: obj hw04utils.c hw04utils.h
	$(COMPILER) $(CFLAGS) -c -o obj/hw04utils.o hw04utils.c

clean:
	$(RM) -r obj
	$(RM) program
	$(RM) hw04.tar.bz2 
	
zip: hw04.tar.bz2
	@echo "Archive created"

hw04.tar.bz2: hw04.tar
	bzip2 hw04.tar

hw04.tar:
	$(RM) hw04.tar.bz2 
	tar -cvf hw04.tar *.c *.h
