program: main.cpp
	$(CXX) -Wall -lm -o program main.cpp

clean:
	$(RM) program
	$(RM) hw05.tar.bz2

zip:
	$(RM) hw05.tar.bz2
	tar -cvf hw05.tar main.cpp config.h
	bzip2 hw05.tar