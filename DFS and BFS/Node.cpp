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

void Node::set_visited() {
	if_visited = true;
}

bool Node::visited() const
{
	return if_visited;
}

std::vector<std::shared_ptr<Node>>::const_iterator Node::cbegin() const
{
	return neighbours.cbegin();
}

std::vector<std::shared_ptr<Node>>::const_iterator Node::cend() const
{
	return neighbours.cend();
}

/*std::vector<std::shared_ptr<Node>> Node::get_neighbours()
{
	return neighbours;
}*/

void Node::set_neighbour(const std::shared_ptr<Node> ptr) {
	neighbours.push_back(ptr);
}

std::vector<std::shared_ptr<Node>>::iterator Node::neighbours_begin()
{
	return neighbours.begin();
}

std::vector<std::shared_ptr<Node>>::iterator Node::neighbours_end()
{
	return neighbours.end();
}

/*void Node::set_neighbour(const NodeID & id) {
	if (!id_is_present(id)) {
		std::shared_ptr<NodeID> ptr (new NodeID(id));
		neighbour_ids.push_back(ptr);
	}
}*/

NodeID Node::get_id() const {
	return id;
}

/*bool Node::id_is_present(const NodeID & id)
{
	auto it = std::find_if(
		neighbour_ids.cbegin(),
		neighbour_ids.cend(),
		[id](const std::shared_ptr<NodeID> ptr) {
			return ptr->operator==(id);
		}
	);
	return it != neighbour_ids.cend();
}*/
