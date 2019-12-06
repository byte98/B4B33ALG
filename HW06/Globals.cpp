#include "Globals.hpp"

template<typename D>
std::map<std::string, D> Globals<D>::getData()
{
	return this->data;
}

template<typename D>
D Globals<D>::getValue(std::string key)
{
	return this->data.at(key);
}

template<typename D>
void Globals<D>::setValue(std::string key, D value)
{
	if (this->data.find(key) == this->data.end())
	{
		this->data.insert({ key, value });
	}
	else
	{
		this->data[key] = value;
	}
}