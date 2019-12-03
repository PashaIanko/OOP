#pragma once
#include "Graph.h"

class MyGraph : public Graph {
public:
	MyGraph() = default;
	~MyGraph() = default;

public:
	virtual std::vector<std::shared_ptr<Node>>
		get_neighbours(const std::shared_ptr<Node>) const override; 
	
	virtual std::shared_ptr<Node> get_first_node() const override; 

	virtual void addNode(const Node& d, std::vector<NodeID> neighbours) override;

	virtual void begin() override;
	virtual void end() override;


private:
	size_t size = 0;
	std::vector<std::shared_ptr<Node>> nodeArray{};
	std::vector<std::shared_ptr<Edge>> edgeArray{};
};