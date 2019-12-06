#ifndef __NODE_HPP__
#define __NODE_HPP__
#include <iostream>
#include <vector>

template <typename T>

///<summary>
///Class representing node in tree
///</summary>
class Node
{
private:
	///<summary>
	///Label of node
	///</summary>
	std::string label;

	///<summary>
	///Childs of nodes
	///</summary>
	std::vector<Node> childs;

	///<summary>
	///Parent of node
	///</summary>
	Node parent;

	///<summary>
	///Data stored in node
	///</summary>
	T data;

public:
	///<summary>
	///Creates new node in tree
	///</summary>
	///<param name="data">Data stored in node</param>
	///<param name="label">Label of node</param>
	Node<T>(T data, std::string label);
};

#endif // !__NODE_HPP__

