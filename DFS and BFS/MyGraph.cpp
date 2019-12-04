#include "pch.h"
#include "MyGraph.h"
#include "NodeID.h"
#include <algorithm>

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

	for (auto it : neighbours) {
		auto if_found = std::find_if
		(
			nodeArray.begin(), nodeArray.end(), 
			[it](const std::shared_ptr<Node> ptr) {
				return ptr->get_id() == it;
			}
		);
		/*если нашли ноду с таким айди - добавляем этот указатель на ноду в вектор соседей
		текущей ноды. В конце добавляем её в вектор нод*/
		if (if_found != nodeArray.end()) {
			//ptr->set_neighbour(*if_found);
		}
	}
	nodeArray.push_back(ptr);
}

void MyGraph::begin() {
}

void MyGraph::end() {
}
