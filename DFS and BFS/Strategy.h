#pragma once
#include <memory>
#include "Graph.h"
#include "Traverser.h"

class Strategy {
public:
	virtual ~Strategy() {};
	void set_traverser(std::shared_ptr<Traverser> traverser_) { traverser = traverser_; }
	virtual void go(Graph&) = 0;// , Traverser&) = 0; /*стратегия обхода, переопределяется в наследниках. */

	void traverser_begin() { traverser->begin(); }
	void traverser_visit_node(Node& node) { traverser->visit_node(node); }
	void traverser_visit_edge(Edge& edge) { traverser->visit_edge(edge); }

private:
	std::shared_ptr<Traverser> traverser{};
};

class DFS_Strategy : public Strategy
{

public:
	~DFS_Strategy() = default;

	virtual void go(Graph& g) override { // , Traverser& tr) override { //const не нужны, ведь методы неконстантные 
														//будут вызываться
		//traverser->begin();//  begin();
		traverser_begin();
		std::shared_ptr<Node> node = g.get_first_node();
		dfs(g, node);
		
	}

private:
	void dfs(Graph& g, std::shared_ptr<Node>& node) {
		if (!node->visited()) {
			traverser_visit_node(*node);
			node->set_visited();
			std::vector<std::shared_ptr<Node>> neighbours = g.get_neighbours(node);
			for (std::vector<std::shared_ptr<Node>>::iterator it = neighbours.begin();

				/*traverser_visit_edge*/
				it != neighbours.end();
				++it) {
				dfs(g, *(it));
			}
		}
	}
};

