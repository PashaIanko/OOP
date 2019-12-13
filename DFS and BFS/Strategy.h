#pragma once
#include <memory>
#include <deque>
#include "Graph.h"


class Traverser;

class Strategy {
public:
	virtual ~Strategy() {};
	void set_traverser(std::shared_ptr<Traverser> traverser_); 
	virtual void go(Graph&, std::shared_ptr<Node>) = 0; // /*стратегия обхода, переопределяется в наследниках. */

	void traverser_begin();
	bool traverser_visit_node(Node& node);
	bool traverser_visit_edge(Edge& edge);

private:
	std::weak_ptr<Traverser> traverser{};
};

class DFS_Strategy : public Strategy {

public:
	~DFS_Strategy() = default;
	virtual void go(Graph& g, std::shared_ptr<Node> start_node) override; 

private:
	void dfs(Graph& g, Node* node);
	bool have_to_exit = false;
};

class BFS_Strategy : public Strategy {
public:
	~BFS_Strategy() = default;
	virtual void go(Graph& g, std::shared_ptr<Node> start_node) override;
private:
	void bfs(Graph& g, Node* node);
private:
	std::deque<Node*> nodes_stack{};
	bool have_to_exit = false;

};

