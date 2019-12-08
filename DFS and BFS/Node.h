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
	//std::vector<std::shared_ptr<Node>> get_neighbours();
	void set_neighbour(const std::shared_ptr<Node> ptr);
	//void set_neighbour(const NodeID& id);
	std::vector<std::shared_ptr<Node>>::iterator neighbours_begin();
	std::vector<std::shared_ptr<Node>>::iterator neighbours_end();

	NodeID get_id() const;
private:
	bool if_visited = false;
	std::vector<std::shared_ptr<Node>> neighbours{};
	//std::vector<std::shared_ptr<NodeID>> neighbour_ids{};
	NodeID id {};
	int data;
	bool id_is_present(const NodeID& id);
};
