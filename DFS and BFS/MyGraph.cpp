#include "pch.h"
#include "MyGraph.h"

std::vector<std::shared_ptr<Node>> MyGraph::get_neighbours(const std::shared_ptr<Node>) const
{
	std::vector<std::shared_ptr<Node>> v{};
	return v;
}

std::shared_ptr<Node> MyGraph::get_first_node() const
{
	if (nodeArray.empty()) {
		std::shared_ptr<Node> invalid_ptr(nullptr);
		return invalid_ptr;
	}
	return *nodeArray.begin();
}

void MyGraph::addNode(const Node & d, std::vector<NodeID> neighbours) {
	std::shared_ptr<Node> ptr(new Node(d));
	nodeArray.push_back(ptr);
}

void MyGraph::begin() {
}

void MyGraph::end() {
}
