#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__
#include <exception>

///<summary>
///Exception thrown when try to add village to map but village
///label is greater than maximal village count
///</summary>
class VillageLabelOutOfBoundaryException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Cannot insert village into map! Village label is out of range for villages.";
	}
};

///<summary>
///Exception thrown when village with set label is not in map
///</summary>
class NotSuchAVillageWithLabelException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Cannot find village in map!";
	}
};

///<summary>
///Exception thrown when there is no path between villages
///<summary>
class NoPathBetweenVillagesException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Cannot find path between villages in map!";
	}
};

#endif // !__EXCEPTIONS_HPP__


