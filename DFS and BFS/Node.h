#pragma once
#include <vector>
#include <memory>
#include "NodeID.h"
/*#include "Graph.h"*/

struct raw_data;

class Node {

public:
	Node() = default;
	Node(const Node& rhs) = default;
	Node(const int data_, const NodeID& id_) : data(data_), id(id_) {};
	Node(const raw_data& data);

	void set_visited();
	bool visited() const;

	std::vector<Node*>::const_iterator cbegin() const;
	std::vector<Node*>::const_iterator cend() const;
	void set_neighbour(Node* ptr);
	std::vector<Node*>::iterator neighbours_begin();
	std::vector<Node*>::iterator neighbours_end();

	NodeID get_id() const;
	int get_data() const;
private:
	bool if_visited = false;
	std::vector<Node*> neighbours{};
	NodeID id {};
	int data;
};
