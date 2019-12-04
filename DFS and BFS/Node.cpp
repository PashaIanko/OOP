#include "pch.h"
#include "Node.h"
#include "NodeID.h"

MyNode::MyNode(const MyNode & rhs) : data(rhs.data) {

}

NodeID MyNode::get_id() const {
	return id;
}

void Node::set_visited() {
	if_visited = true;
}

bool Node::visited() const
{
	return if_visited;
}

std::vector<std::shared_ptr<Node>> Node::get_neighbours()
{
	return neighbours;
}

NodeID Node::get_id() const {
	NodeID default_id;
	return default_id;
}
