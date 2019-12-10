#ifndef __GLOBALS_HPP__
#define __GLOBALS_HPP__
#include <map>
#include <string>


///<summary>
///Class conatining global variables
///</summary>
class Globals
{

private:

	///<summary>
	///Values stored in globals
	///</summary>
	std::map<std::string, int> values;

	///<summary>
	///Pointer to instance of globals
	///</summary>
	static Globals* instance;
	///<summary>
	///Instances new globals
	///</summary>
	Globals();

public:
	///<summary>
	///Gets instance of globals
	///</summary>
	///<returns>Instance of globals</returns>
	static Globals* getInstance();

	///<summary>
	///Gets all values stored in globals
	///</summary>
	///<returns>All values stored in globals</returns>
	std::map<std::string, int> getValues();

	///<summary>
	///Sets value of global variable
	///</summary>
	///<param name="key">Name of global variable</param>
	///<param name="value">Data which will be set to global variable</param>
	void setValue(std::string key, int value);

	///<summary>
	///Gets value of global variable
	///</summary>
	///<param name="key">Name of global variable</param>
	///<returns>Value of global variable</returns>
	int getValue(std::string key);
};
#endif // !__GLOBALS_HPP__