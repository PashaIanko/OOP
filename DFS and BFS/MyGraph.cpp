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
	/*neighbours - � ������ �������� � ���� ������� ����������� ����*/
	std::shared_ptr<Node> ptr(new Node(d));
	for (auto it : neighbours) {
		std::shared_ptr<Node> neighbour = node_is_present(it);
		if (neighbour) {/*���� �� ������ ������ � ����� ������������ ����� ����*/
			ptr->set_neighbour(neighbour);
			neighbour->set_neighbour(ptr);/*��������������� - ��� ���� ���� 
									  �����, � �������� � ��� ������ ������*/
		}
	}
	nodeArray.insert(ptr);// .push_back(ptr);
	/*���������� ����, ���������� �� ������� �� �������
						   ��������� � ��� ��������������� �����*/
}

void MyGraph::addNode(const Node & node, const NodeID & connect_to) {
	std::shared_ptr<Node> ptr(new Node(node));
	std::shared_ptr<Node> neighbour = node_is_present(connect_to);
	if (neighbour) {
		ptr->set_neighbour(neighbour);
		neighbour->set_neighbour(ptr);
	}
	nodeArray.insert(ptr);
}


void MyGraph::addNode(const Node & d) {
	if (!node_is_present(d)) { /*���� ���� � ����� id ��� �� ���� ������*/
		std::shared_ptr<Node> ptr(new Node(d));
		nodeArray.insert(ptr);//push_back(ptr);
	}
}

void MyGraph::begin() {
}

void MyGraph::end() {
}

bool MyGraph::all_visited() const
{
	auto it = std::find_if
	(
		nodeArray.cbegin(),
		nodeArray.cend(),
		[](const std::shared_ptr<Node> ptr) {
			return !(ptr->visited());
		}
	);
	return it == nodeArray.cend();
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
	/*����� ���� neighbour ����� ������ ������ - node
}*/
