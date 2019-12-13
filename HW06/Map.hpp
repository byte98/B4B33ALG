#ifndef __MAP_HPP__
#define __MAP_HPP__

///<summary>
///Default value of distance which sets two villages with no path between them
///</summary>
#define VILLAGE_UNAVIALABLE -1

#include "Village.hpp"
#include "config.h"
#include <vector>
#include <queue>

///<summary>
///Class representing map with villages
///</summary>
class Map
{
private:
	///<summary>
	///Array with villages which are on map
	///</summary>
	Village** villages;

	///<summary>
	///Count of villages on map
	///</summary>
	int villages_count;

	///<summary>
	///Recursive function which finds shortes path between villages
	///</summary>
	void findShortestPath(std::queue<Village*>* villages, Village* actual);

public:
	///<summary>
	///Creates new map with villages
	///</summary>
	///<param name="villages">Count of villages on map</param>
	///<returns>New instance of map</returns>
	Map(int villages);

	///<summary>
	///Adds village to map
	///</summary>
	///<param name="village">Village which will be added to map</param>
	void addVillage(Village* village);

	///<summary>
	///Gets village by its label
	///</summary>
	///<param name="label">Label of village</param>
	///<returns>Village with set label or <c>NULL</c></returns>
	Village* getVillage(int label);

	///<summary>
	///Makes path between two villages
	///</summary>
	///<param name="villageA">Starting village</param>
	///<param name="villageB">Finishing village</param>
	///<param name="cost">Cost of path between starting and finishing village</param>
	void makePath(Village* villageA, Village* villageB, int cost);

	///<summary>
	///Gets cost of path between villages
	///</summary>
	///<param name="villageA">Starting village</param>
	///<param name="villageB">Finishing village</param>
	///<returns>Cost of path between starting and finishing village</returns>
	int getCost(Village* villageA, Village* villageB);

	///<summary>
	///Gets paths leading from village
	///</summary>
	///<param name="village">Village which paths from will be returned</param>
	///<returns>Paths leading from village</returns>
	std::vector<Path<Village*>*>* getPaths(Village* village);

	///<summary>
	///Gets neighbour villages available from one village
	///</summary>
	///<param name="village">Village which neighbours will be returned</param>
	///<returns>Neighbour villages from set village</returns>
	std::vector<Village*>* getNeighbours(Village* village);

	///<summary>
	///Gets shortest path between two villages
	///</summary>
	///<param name="start_village">Starting village of shortest path finding</param>
	///<param name="final_village">Final village of shortest path finind</param>
	///<returns>Vector with villages visited during finding shortest path finindg</returns>
	std::vector<Village*>* findPath(Village* start_village, Village* final_village);

	~Map();

};

#endif // ! __MAP_HPP__

