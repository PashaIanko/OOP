#pragma once
#include <vector>
#include <memory>
#include "NodeID.h"


class Node {

public:
	Node() = default;
	Node(const Node& rhs) = default;
	Node(const int data_, const NodeID& id_) : data(data_), id(id_) {};

	void set_visited();
	bool visited() const;

	std::vector<std::shared_ptr<Node>>::const_iterator cbegin() const;
	std::vector<std::shared_ptr<Node>>::const_iterator cend() const;
	void set_neighbour(const std::shared_ptr<Node> ptr);
	std::vector<std::shared_ptr<Node>>::iterator neighbours_begin();
	std::vector<std::shared_ptr<Node>>::iterator neighbours_end();

	NodeID get_id() const;
	int get_data() const;
private:
	bool if_visited = false;
	std::vector<std::shared_ptr<Node>> neighbours{};
	NodeID id {};
	int data;
};
