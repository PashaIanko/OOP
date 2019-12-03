#include "pch.h"
#include "Node.h"

MyNode::MyNode(const MyNode & rhs) : data(rhs.data) {

}

void Node::set_visited() {
	if_visited = true;
}

std::vector<std::shared_ptr<Node>> Node::get_neighbours()
{
	return neighbours;
}
