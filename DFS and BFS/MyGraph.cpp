#include "pch.h"
#include "MyGraph.h"
#include "NodeID.h"
#include "Node.h"
#include <algorithm>

std::shared_ptr<Node> MyGraph::get_first_node() const
{
	if (nodeArray.empty()) {
		std::shared_ptr<Node> invalid_ptr(nullptr);
		return invalid_ptr;
	}
	return *nodeArray.begin();
}

void MyGraph::addNode(const Node & d, std::vector<NodeID> neighbours) {
	/*neighbours - с какими соседями я хочу связать добавляемую ноду*/
	std::shared_ptr<Node> ptr(new Node(d));
	for (auto it : neighbours) {
		std::shared_ptr<Node> neighbour = node_is_present(it);
		if (neighbour) {/*если на данный момент в графе присутствует такая нода*/
			ptr->set_neighbour(neighbour);
			neighbour->set_neighbour(ptr);/*двунаправленный - эту ноду надо 
									  найти, и добавить к ней нового соседа*/
		}
	}
	nodeArray.push_back(ptr);
	/*двусвязный граф, проходимся по соседям из вектора
						   добавляем к ним двунаправленную связь*/
}

void MyGraph::addNode(const Node & d){
	if (!node_is_present(d)) { /*если ноды с таким id нет на этот момент*/
		std::shared_ptr<Node> ptr(new Node(d));
		nodeArray.push_back(ptr);
	}
}

void MyGraph::begin() {
}

void MyGraph::end() {
}

class equal_id {
public:
	equal_id(const Node& n_) : n(n_) {};
	bool operator() (const std::shared_ptr<Node> ptr) {
		return (n.get_id() == ptr->get_id());
	}
private:
	Node n;
};

std::shared_ptr<Node> MyGraph::node_is_present(const Node & n) const {
	auto it = std::find_if
	(
		nodeArray.begin(), 
		nodeArray.end(),
		equal_id(n)
		/*[n](std::shared_ptr<Node> ptr) {
			//return ptr->get_id() == n.get_id();
		return true;
		}*/
	);
	if (it == nodeArray.end()) {
		std::shared_ptr<Node> ptr(nullptr);
		return ptr;
	}
	return *it;// != nodeArray.cend();
}

std::shared_ptr<Node> MyGraph::node_is_present(const NodeID & id) const
{
	auto it = std::find_if
	(
		nodeArray.begin(),
		nodeArray.end(),
		[id] (const std::shared_ptr<Node> ptr) {
			return ptr->get_id() == id;
		//return true;
		}
	);
	if (it == nodeArray.end()) {
		std::shared_ptr<Node> ptr(nullptr);
		return ptr;
	}
	return *it;// != nodeArray.cend();
}

/*void MyGraph::set_neighbour_node(std::shared_ptr<Node> neighbour, const Node& node) {
	/*здесь ноде neighbour задаём нового соседа - node
}*/
