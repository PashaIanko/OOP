#pragma once
#include <vector>
#include <memory>

class Node {

public:
	void set_visited() { if_visited = true; }
	bool visited() const { return if_visited; }

	std::vector<std::shared_ptr<Node>>::const_iterator cbegin() const { return neighbours.cbegin(); }
	std::vector<std::shared_ptr<Node>>::const_iterator cend() const { return neighbours.cend(); }

	

private:
	bool if_visited = false;
	std::vector<std::shared_ptr<Node>> neighbours{};

};

class MyNode : public Node {

public:
	MyNode(const int data_) : data(data_) {}
	~MyNode() = default;
private:
	int data;
};