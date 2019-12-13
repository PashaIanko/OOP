#pragma once
#include <vector>
#include <memory>
#include "Node.h"
#include "Edge.h"


class Graph {
public:
	virtual std::shared_ptr<Node> get_first_node() const = 0;
	/*virtual std::vector<std::shared_ptr<Node>> 
		get_neighbours(const std::shared_ptr<Node>) const = 0;*/

	virtual void begin() =0; //можно не переопределять, по желанию, не делаю чисто виртуальной
	virtual void end() =0;

	//std::shared_ptr<Edge> get_edge(const Node& from, const Node& to);
	
	virtual void addNode(const Node&) {};
	virtual void addNode(const Node&, const NodeID&) {};
	virtual void addNode(const Node&, std::vector<NodeID>) {};
};

