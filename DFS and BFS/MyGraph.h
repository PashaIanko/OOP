#pragma once
#include "Graph.h"

class MyGraph : public Graph {
public:
	MyGraph(size_t size_) : size(size_) { nodeArray.resize(size_); };
	~MyGraph() = default;

public:
	virtual std::vector<std::shared_ptr<Node>>
		get_neighbours(const std::shared_ptr<Node>) const override {
		std::vector<std::shared_ptr<Node>> v{};
		return v;
	}
	virtual std::shared_ptr<Node> get_first_node() const override {
		return nullptr;
	}

	virtual void addNode(const Node& d) override {
		
	};


private:
	size_t size = 0;
	std::vector<std::shared_ptr<Node>> nodeArray{};
};