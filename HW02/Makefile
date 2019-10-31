COMPILER=clang
CFLAGS+=-Wall
all: program

program: main.o experiment.o utils.o laboratory.o queue.o dynamic_queue.o
	$(COMPILER) $(CFLAGS) -lm ./obj/utils.o ./obj/queue.o ./obj/dynamic_queue.o ./obj/laboratory.o ./obj/experiment.o ./obj/main.o  -o ./program

obj:
	mkdir ./obj

main.o: obj main.c
	$(COMPILER) $(CFLAGS) -c ./main.c -o ./obj/main.o

experiment.o: obj experiment.c
	$(COMPILER) $(CFLAGS) -c ./experiment.c -o ./obj/experiment.o

utils.o: obj utils.c
	$(COMPILER) $(CFLAGS) -c ./utils.c -o ./obj/utils.o

laboratory.o: obj laboratory.c
	$(COMPILER) $(CFLAGS) -c -lm ./laboratory.c -o ./obj/laboratory.o

queue.o: obj queue.c
	$(COMPILER) $(CFLAGS) -c ./queue.c -o ./obj/queue.o

dynamic_queue.o: obj dynamic_queue.c
	$(COMPILER) $(CFLAGS) -c ./dynamic_queue.c -o ./obj/dynamic_queue.o

clean:
	$(RM) -r ./obj
	$(RM) ./program