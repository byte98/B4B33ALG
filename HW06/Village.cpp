#include "Village.hpp"
#include <iostream>

Village::Village() : label(-1), visit_time(1), tourist_index(-1)
{
	this->paths = new std::vector<Path<Village*>*>();
}

Village::Village(int label, int visit_time) : label(label), visit_time(visit_time), tourist_index(-1)
{
	this->paths = new std::vector<Path<Village*>*>();
}

int Village::getLabel()
{
	return this->label;
}

int Village::getVisitTime()
{
	return this->visit_time;
}

void Village::addNeighbour(Village* village, int cost)
{
	Village** start = new Village * (this);
	Village** finish = &village;
	Path<Village*>* path = new Path<Village*> (start, finish, cost);
	this->paths->push_back(path);
}

std::vector<Path<Village*>*>* Village::getPaths()
{
	return this->paths;
}

void Village::setAtractiveness(int tourist_index)
{
	this->tourist_index = tourist_index;
}

int Village::getAtractiveness()
{
	return this->tourist_index;
}

Village::~Village()
{
}
