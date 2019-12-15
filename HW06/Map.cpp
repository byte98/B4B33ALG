#include "Map.hpp"
#include "Exceptions.hpp"
#include "Path.hpp"
#include <iostream>
#include <queue>
#include "Globals.hpp"

void Map::findShortestPath(std::queue<Village*>* villages, Village* actual, Village* final_village)
{
	std::vector<Path<Village*>*>* neighbours = actual->getPaths();
	Globals* settings = Globals::getInstance();
	
	for (int i = 0; i < neighbours->size(); i++)
	{
		Village* final_node = neighbours->at(i)->getFinalNode();
		if (final_node->getLabel() == final_village->getLabel())
		{
#ifdef DEBUG
			std::cout << "\tFinal village reached!" << std::endl;
#endif // DEBUG
			settings->setValue("SHORTEST PATH", 1);
			while (villages->empty() == false)
			{
				villages->pop();
			}
			break;
		}
		else
		{
			villages->push(neighbours->at(i)->getFinalNode());
		}
	}
}

Map::Map(int villages)
{
	this->villages_count = villages;
	this->villages = new Village*[this->villages_count];
}

void Map::addVillage(Village* village)
{
	int label = village->getLabel();
	if (label >= this->villages_count)
	{
		throw VillageLabelOutOfBoundaryException();
	}
	else
	{
		this->villages[label] = village;
	}
}

Village* Map::getVillage(int label)
{
	if (this->villages[label]->getLabel() == label)
	{
		return this->villages[label];
	}
	else
	{
		for (int i = 0; i < this->villages_count; i++)
		{
			if (this->villages[i]->getLabel() == label)
			{
				return this->villages[i];
			}
		}
	}
	throw NotSuchAVillageWithLabelException();
}

void Map::makePath(Village* villageA, Village* villageB, int cost)
{
	villageA->addNeighbour(villageB, cost);
}

int Map::getCost(Village* villageA, Village* villageB)
{
	int reti = -1;
	/*
	std::vector<Path<Village*>*>* neighbours = villageA->getPaths();
	std::vector<Path<Village*>*>::iterator it = neighbours->begin();
	while (it != neighbours->end())
	{
		if (*(*it)->getFinalNode()->getLabel() == villageB->getLabel())
		{
			reti = *(*it)->getCost();
			break;
		}
		it++;
	}
	if (reti == -1)
	{
		throw NoPathBetweenVillagesException();
	}
	*/
	return reti;
}

std::vector<Path<Village*>*>* Map::getPaths(Village* village)
{
	return village->getPaths();
}

std::vector<Village*>* Map::getNeighbours(Village* village)
{
	std::vector<Path<Village*>*>* paths = this->getPaths(village);
	std::vector<Village*>* reti = new std::vector<Village*>();

	std::vector<Path<Village*>*>::iterator it = paths->begin();
	while ((it) != paths->end())
	{
		reti->push_back(*(*it)->getFinalNode());
		it++;
	}

	return reti;
}


std::vector<Village*>* Map::findPath(Village* start_village, Village* final_village)
{
	std::vector<Village*>* reti = new std::vector<Village*>();

	std::queue<Village*>* village_queue = new std::queue<Village*>();
	village_queue->push(start_village);

	Globals* settings = Globals::getInstance();

	while (village_queue->empty() == false && settings->getValue("SHORTEST PATH") == -1)
	{
		Village* actual = village_queue->front();
		village_queue->pop();
		this->findShortestPath(village_queue, actual, final_village); 
	}

	return reti;
}

Map::~Map()
{
}
