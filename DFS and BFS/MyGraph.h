#pragma once
#include "Graph.h"

class MyGraph : public Graph {
public:
	MyGraph() = default;
	~MyGraph() = default;

public:
	
	virtual std::shared_ptr<Node> get_first_node() const override; 
	virtual void addNode(const Node& d, std::vector<NodeID> neighbours) override;
	virtual void addNode(const Node& d) override;

	virtual void begin() override;
	virtual void end() override;

	bool all_visited() const;

private:
	size_t size = 0;
	std::vector<std::shared_ptr<Node>> nodeArray{};
	//std::vector<std::shared_ptr<Edge>> edgeArray{};
	std::shared_ptr<Node> node_is_present(const Node& n) const;
	std::shared_ptr<Node> node_is_present(const NodeID& id) const;
	//void set_neighbour_node(std::shared_ptr<Node> neighbour, const Node& node);
};