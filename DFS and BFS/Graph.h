#pragma once
#include <vector>
#include <memory>
#include "Data.h"
#include "Node.h"



class Graph {
public:
	virtual std::shared_ptr<Node> get_first_node() const = 0;
	virtual std::vector<std::shared_ptr<Node>> 
		get_neighbours(const std::shared_ptr<Node>) const = 0;
	
	virtual void addNode(const Node& d) = 0;
};

