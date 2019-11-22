#pragma once

#include <vector>

class Node {

public:
	void set_visited() { if_visited = true; }

private:
	bool if_visited = false;
	std::vector<Node*> neighbours{};
};

using citerator = ConstGraphIterator;

class ConstGraphIterator {

public:
	void set_visited() { data->set_visited(); };
	Node* get_data() { return data; };
private:
	bool if_visited = false;
	std::vector<Node*> neighbours {};
	Node* data = nullptr;
};

class Graph {
public:
	virtual ConstGraphIterator cbegin() const = 0;
	virtual ConstGraphIterator cend() const = 0;
};

class MyGraph : public Graph {

	

	MyGraph(int size); //Constructor of the class
	~MyGraph() = default;

public:

	citerator cbegin() const override {

	}
	

	void addNode(int node);
	void addUEdge(int node1, int node2);
	int connectedComponents(void);
	int checkNode(int node);
	int checkEdge(int node1, int node2);
	void deleteNode(int node);
	void deleteUEdge(int node1, int node2);
	void printNodeList(void);
	

private:
	int graphSize;
	std::vector<int> nodeArray;
	std::vector<int> edge1Array;
	std::vector<int> edge2Array;
	void addEdge(int node1, int node2);
	void deleteEdge(int node1, int node2);
};