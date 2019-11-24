COMPILER=clang
CFLAGS+=-Wall

program: main.o consolecolor.o consolecolorutils.o
	$(COMPILER) $(CFLAGS) -o program ./main.o ./consolecolor.o ./consolecolorutils.o

main.o: main.c
	$(COMPILER) $(CFLAGS) -c -o main.o main.c

consolecolor.o: ConsoleColor.c ConsoleColor.h consolecolorutils.o
	$(COMPILER) $(CFLAGS) -c -o consolecolor.o ConsoleColor.c

consolecolorutils.o: ConsoleColor_utils.h ConsoleColor_utils.c
	$(COMPILER) $(CFLAGS) -c -o consolecolorutils.o ConsoleColor_utils.c