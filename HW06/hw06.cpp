#include <iostream>
#include <cstdlib>
#include "Globals.hpp"
#include "config.h"

using namespace std;


int main(int argc, char* argv[])
{
	int reti = EXIT_SUCCESS;

	Globals<int> settings = Globals<int>::getInstance();
	int number_of_villages, starting_village, ending_village, maximal_time = -1;
	std::cin >> number_of_villages;
	std::cin >> starting_village;
	std::cin >> ending_village;
	std::cin >> maximal_time;

	settings.setValue("NUMBER OF VILLAGES", number_of_villages);
	settings.setValue("STARTING VILLAGE", starting_village);
	settings.setValue("ENDING VILLAGE", ending_village);
	settings.setValue("MAXIMAL TIME", maximal_time);

#ifdef DEBUG
	map<string, int>::iterator it;
	std::cout << "Loaded settings: " << std::endl;
	for (it = settings.getData().begin(); it != settings.getData().end(); it++)
	{
		std::cout << "\t" 
			<< it->first  // string (key)
			<< ':'
			<< it->second   // string's value 
			<< std::endl;
	}
#endif // DEBUG

	return reti;
}