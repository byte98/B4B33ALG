#include "Map.hpp"
#include "Exceptions.hpp"
#include "Path.hpp"
#include <iostream>
#include <queue>
#include "Globals.hpp"

void Map::findShortestPath(std::queue<Village*>* villages, Village* actual)
{
	Globals* settings = Globals::getInstance();
#ifdef DEBUG
	std::cout << "\t\t" << actual->getLabel() << std::endl;
#endif // DEBUG
	if (actual->getLabel() == settings->getValue("FINAL VILLAGE"))
	{
#ifdef DEBUG
		std::cout << "\t Found final village!" << std::endl;
#endif // DEBUG
		settings->setValue("SHORTEST PATH", 1);
		return;
	}
	else
	{
		std::vector<Path<Village*>*>* neighbours = actual->getPaths();
		std::vector<Path<Village*>*>::iterator it = neighbours->begin();
		while (it != neighbours->end())
		{
			villages->push(*(*it)->getFinalNode());
			it++;
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

	std::queue<Village*>* tree_queue = new std::queue<Village*>();
	tree_queue->push(start_village);
	while (tree_queue->empty() == false)
	{

	}

	return reti;
}

Map::~Map()
{
}
