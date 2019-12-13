#include <iostream>
#include <cstdlib>
#include "Globals.hpp"
#include "Map.hpp"
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
	settings->setValue("FINAL VILLAGE", ending_village);
	settings->setValue("MAXIMAL TIME", maximal_time);

#ifdef DEBUG
	cout << "--- Loaded data ---" << endl;
	printf("\tNUMBER OF VILLAGES: %d\n", settings->getValue("NUMBER OF VILLAGES"));
	printf("\tSTARTING VILLAGE: %d\n", settings->getValue("STARTING VILLAGE"));
	printf("\tENDING VILLAGE: %d\n", settings->getValue("FINAL VILLAGE"));
	printf("\tMAXIMAL TIME: %d\n", settings->getValue("MAXIMAL TIME"));
#endif // DEBUG

	//Create map of villages
	Map villages = Map(settings->getValue("NUMBER OF VILLAGES"));

	//Load villages visit times
#ifdef DEBUG
	cout << "--- Loading villages --- " << endl;
#endif // DEBUG

	for (int i = 0; i < settings->getValue("NUMBER OF VILLAGES"); i++)
	{
		int time = 0;
		cin >> time;
		villages.addVillage(new Village(i, time));
#ifdef DEBUG
		cout << "\t" << "[" << i << "] (" << time << ")" << endl;
#endif // DEBUG

	}

	//Load attractivenesses of villages
#ifdef DEBUG
	cout << "--- Loading tourist indexes ---" << endl;
#endif // DEBUG

	for (int i = 0; i < settings->getValue("NUMBER OF VILLAGES"); i++)
	{
		int tourist_index;
		cin >> tourist_index;
		villages.getVillage(i)->setAtractiveness(tourist_index);
#ifdef DEBUG
		cout << "\t[" << i << "] >" << tourist_index << "<" << endl;
#endif // DEBUG

	}

	//Load paths between villages
#ifdef DEBUG
	cout << "--- Loading paths ---" << endl;
#endif // DEBUG

	for (int i = 0; i < settings->getValue("NUMBER OF VILLAGES") - 1; i++)
	{
		int start, finish, cost;
		cin >> start;
		cin >> finish;
		cin >> cost;
#ifdef DEBUG
		cout << "\t[" << start << "] -> [" << finish << "] @ " << cost << endl;
#endif // DEBUG

		villages.makePath(villages.getVillage(start), villages.getVillage(finish), cost);
	}

#ifdef DEBUG
	cout << "\t --- Available paths ---" << endl;
	for (int i = 0; i < settings->getValue("NUMBER OF VILLAGES"); i++)
	{
		try
		{
			Village* v = villages.getVillage(i);
			cout << "\t\t[" << v->getLabel() << "]: " << v->getPaths()->size() << endl;
		}
		catch (const std::exception& ex)
		{
			cout << endl << "[" << i << "]" << ex.what() << endl;
		}
	}
#endif // DEBUG


	
	//Find shortest path from start to final village
#ifdef DEBUG
	cout << "--- Finding shortest path ---" << endl;
#endif // DEBUG
	settings->setValue("SHORTEST PATH", -1);
	villages.findPath(villages.getVillage(settings->getValue("STARTING VILLAGE")), villages.getVillage(settings->getValue("FINAL VILLAGE")));
	
	return reti;
}