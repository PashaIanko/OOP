#pragma once
#include "Graph.h"
#include <set>

struct IDCompare {
	bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) const {
		return a->get_id() < b->get_id();
	}
};

class MyGraph : public Graph {
public:
	MyGraph() = default;
	~MyGraph() = default;

public:
	
	virtual std::shared_ptr<Node> get_first_node() const override; 
	virtual void addNode(const Node& d, std::vector<NodeID> neighbours) override;
	virtual void addNode(const Node& node, const NodeID& connect_to) override; /*с одним соседом, куда
																			   подсоединяемся*/
	virtual void addNode(const Node& d) override;

	virtual void begin() override;
	virtual void end() override;

	bool all_visited() const;

private:
	size_t size = 0;
	//std::vector<std::shared_ptr<Node>> nodeArray{};
	std::set<std::shared_ptr<Node>, IDCompare> nodeArray{}; /*Храню упорядочено*/
	std::shared_ptr<Node> node_is_present(const Node& n) const;
	std::shared_ptr<Node> node_is_present(const NodeID& id) const;
	
};