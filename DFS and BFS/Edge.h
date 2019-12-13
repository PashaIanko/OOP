#pragma once
#include "Node.h"

class Edge {
public:
	Edge() = delete;
	Edge(Node* from_, Node* to_) : 
		from(from_), 
		to(to_),
		id_from(from_->get_id()), 
		id_to(to_->get_id())
	{}
	Edge(const NodeID& from_, const NodeID& to_) : id_from(from_), id_to(to_) {}
	bool operator==(const Edge& rhs) const;
private:
	Node* from {};
	Node* to{};
	NodeID id_from {};
	NodeID id_to {};

};