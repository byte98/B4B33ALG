#include "Node.hpp"

template <typename T>
Node<T>::Node(T data, std::string label)
{
	this->childs = std::vector<Node>();
	this->data = data;
	this->label = label;
}