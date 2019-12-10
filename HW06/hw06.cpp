#include <iostream>
#include <cstdlib>
#include "Globals.hpp"
#include "config.h"

using namespace std;


int main(int argc, char* argv[])
{
	int reti = EXIT_SUCCESS;

	Globals* settings = Globals::getInstance();

	//Load first line of input
	int number_of_villages, starting_village, ending_village, maximal_time = -1;
	cin >> number_of_villages;
	cin >> starting_village;
	cin >> ending_village;
	cin >> maximal_time;

	//Save it as globals variables
	settings->setValue("NUMBER OF VILLAGES", number_of_villages);
	settings->setValue("STARTING VILLAGE", starting_village);
	settings->setValue("ENDING VILLAGE", ending_village);
	settings->setValue("MAXIMAL TIME", maximal_time);



#ifdef DEBUG
	cout << "--- Loaded data ---" << endl;
	printf("\tNUMBER OF VILLAGES: %d\n", settings->getValue("NUMBER OF VILLAGES"));
	printf("\tSTARTING VILLAGE: %d\n", settings->getValue("STARTING VILLAGE"));
	printf("\tENDING VILLAGE: %d\n", settings->getValue("ENDING VILLAGE"));
	printf("\tMAXIMAL TIME: %d\n", settings->getValue("MAXIMAL TIME"));
#endif // DEBUG

	return reti;
}