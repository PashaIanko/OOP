#pragma once
#include <vector>
#include <memory>
#include "NodeID.h"


class Node {

public:
	Node() = default;
	Node(const Node& rhs) = default;
	void set_visited();
	bool visited() const;

	std::vector<std::shared_ptr<Node>>::const_iterator cbegin() const { return neighbours.cbegin(); }
	std::vector<std::shared_ptr<Node>>::const_iterator cend() const { return neighbours.cend(); }
	std::vector<std::shared_ptr<Node>> get_neighbours();

	virtual NodeID get_id() const;
private:
	bool if_visited = false;
	std::vector<std::shared_ptr<Node>> neighbours{};

};

class MyNode : public Node {

public:
	MyNode(const MyNode& rhs);
	MyNode(const int data_, const NodeID& id_) : id(id_), data(data_) {}
	~MyNode() = default;

	virtual NodeID get_id() const override;

private:
	NodeID id{};
	int data {};
	
};