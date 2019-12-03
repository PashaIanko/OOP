#pragma once
#include <vector>
#include <memory>

class NodeID {
public:
	NodeID() = default;
	NodeID(int id_) : id(id_) {};
private:
	int id {};
};

class Node {

public:
	Node() = default;
	Node(const Node& rhs) = default;
	void set_visited();// { if_visited = true; }
	bool visited() const { return if_visited; }

	std::vector<std::shared_ptr<Node>>::const_iterator cbegin() const { return neighbours.cbegin(); }
	std::vector<std::shared_ptr<Node>>::const_iterator cend() const { return neighbours.cend(); }
	
	std::vector<std::shared_ptr<Node>> get_neighbours();

private:
	bool if_visited = false;
	std::vector<std::shared_ptr<Node>> neighbours{};

};

class MyNode : public Node {

public:
	MyNode(const MyNode& rhs);
	MyNode(const int data_, const NodeID& id_) : id(id_), data(data_) {}
	~MyNode() = default;

private:
	NodeID id{};
	int data {};
	
};