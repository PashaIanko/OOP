#include "pch.h"
#include "Node.h"
#include "NodeID.h"
#include <algorithm>

//MyNode::MyNode(const MyNode & rhs) : data(rhs.data) {
//
//}
//
//NodeID MyNode::get_id() const {
//	return id;
//}
#include "RawData.h"

Node::Node(const raw_data & data_) : data(data_.data), id(data_.id) {}

void Node::set_visited() {
	if_visited = true;
}

bool Node::visited() const
{
	return if_visited;
}

std::vector<Node*>::const_iterator Node::cbegin() const
{
	return neighbours.cbegin();
}

std::vector<Node*>::const_iterator Node::cend() const
{
	return neighbours.cend();
}


void Node::set_neighbour(Node* ptr) {
	neighbours.push_back(ptr);
}

std::vector<Node*>::iterator Node::neighbours_begin()
{
	return neighbours.begin();
}

std::vector<Node*>::iterator Node::neighbours_end()
{
	return neighbours.end();
}

NodeID Node::get_id() const {
	return id;
}

int Node::get_data() const
{
	return data;
}

