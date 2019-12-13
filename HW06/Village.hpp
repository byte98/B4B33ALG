#ifndef __VILLAGE_HPP__
#define __VILLAGE_HPP__
#include <vector>
#include "Path.hpp"

///<summary>
///Class representing village in map
///</summary>
class Village
{
private:
	///<summary>
	///Label of village
	///</summary>
	int label;

	///<summary>
	///Time needed for visit village
	///</summary>
	int visit_time;

	///<summary>
	///Paths from village
	///</summary>
	std::vector<Path<Village*>*>* paths;

	///<summary>
	///Count of paths from village
	///</summary>
	int paths_count = 0;

	///<summary>
	///Attractiveness of village for tourists
	///</summary>
	int tourist_index;

public:
	///<summary>
	///Creates new empty village
	///</summary>
	///<returns>Empty village</returns>
	Village();

	///<summary>
	///Creates new village
	///</summary>
	///<param name="label">Label of village</param>
	///<param name="visit_time">Time needed for visit village</param>
	///<returns>New instance of village class</returns>
	Village(int label, int visit_time);

	///<summary>
	///Gets label of village
	///</summary>
	///<returns>Label of village</returns>
	int getLabel();

	///<summary>
	///Gets time needed for visit village
	///</summary>
	///<returns>Time needed for visit village</returns>
	int getVisitTime();

	///<summary>
	///Adds neihbour village to village
	///</summary>
	///<param name="village">Neighbour village</param>
	///<param name="cost">Cost of the path to the neighbour village</param>
	void addNeighbour(Village* village, int cost);

	///<summary>
	///Gets path from village
	///</summary>
	///<returns>Paths leading from village</returns>
	std::vector<Path<Village*>*>* getPaths();

	///<summary>
	///Sets attractiveness of village for tourist
	///</summary>
	///<param name="tourist_index">Value of attractiveness of village for tourist</param>
	void setAtractiveness(int tourist_index);

	///<summary>
	///Gets attractiveness of village
	///</summary>
	///<returns>Attractiveness of village</returns>
	int getAtractiveness();

	~Village();
};

#endif // __VILLAGE_HPP__

