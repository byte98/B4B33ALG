CXX=g++
CFLAGS+=-Wall

program: obj/hw06.o obj/node.o obj/globals.o
	$(CXX) $(CFLAGS) -o program obj/hw06.o obj/node.o obj/globals.o

obj:
	mkdir obj

obj/hw06.o: obj
	$(CXX) $(CFLAGS) -c -o obj/hw06.o hw06.cpp

obj/node.o: Node.cpp Node.hpp
	$(CXX) $(CFLAGS) -c -o obj/node.o Node.cpp

obj/globals.o: Globals.cpp Globals.hpp
	$(CXX) $(CFLAGS) -c -o obj/globals.o Globals.cpp

clean:
	$(RM) program
	$(RM) -r obj