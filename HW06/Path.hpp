#ifndef __PATH_HPP__
#define __PATH_HPP__


template <class Node>

///<summary>
///Class representing path between two villages
///</summary>
class Path
{
private:
	///<summary>
	///Starting node of path
	///</summary>
	Node* starting_node;

	///<summary>
	///Final node of path
	///</summary>
	Node* final_node;

	///<summary>
	///Cost of path
	///</summary>
	int cost;

public:
	///<summary>
	///Creates new path between villages
	///</summary>
	///<param name="starting_node">Starting node of path</param>
	///<param name="final_node">Final node of path</param>
	///<param name="cost">Cost of path</param>
	///<returns>New instance of path</returns>
	Path(Node* starting_node, Node* final_node, int cost);

	///<summary>
	///Gets starting node of path
	///</summary>
	///<returns>Starting node of path</returns>
	Node* getStartingNode();

	///<summary>
	///Gets final node of path
	///</summary>
	///<returns>Final node of path</returns>
	Node* getFinalNode();

	///<summary>
	///Gets cost of path
	///</summary>
	///<returns>Cost of path</returns>
	int getCost();



	~Path();
};

template <class Node>
Path<Node>::Path(Node* starting_node, Node* final_node, int cost) :
	starting_node(starting_node),
	final_node(final_node),
	cost(cost)
{
}

template <class Node>
Node* Path<Node>::getStartingNode()
{
	return this->starting_node;
}

template <class Node>
Node* Path<Node>::getFinalNode()
{
	return this->final_node;
}

template <class Node>
int Path<Node>::getCost()
{
	return this->cost;
}
template<class Node>
inline Path<Node>::~Path()
{
}
#endif // !__PATH_HPP__
