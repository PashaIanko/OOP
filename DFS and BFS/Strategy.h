#pragma once
#include <memory>
#include "Graph.h"

/*class Traversion
{
public:
	virtual ~Traversion() {}
	virtual void traverse(const Graph& ) = 0;
};

//template<typename Strategy>
class Traverser_
{
public:
	~Traverser_() = default;

	template<typename Strategy>
	static void traverse(const Graph& g);
};



class BFS_Traversion : public Traversion
{
public:
	void traverse(const Graph& g) override {
		
	}

	static void bfs(const std::shared_ptr<Node>& node, const Graph& g) {

	}
};

class DFS_Traversion : public Traversion
{
	
public:
	void traverse(const Graph& g) override {
		
		std::shared_ptr<Node> first_node = g.get_first_node();
		dfs(first_node, g);
	}

public:
	static void dfs(const std::shared_ptr<Node>& node, const Graph& g) {
		if (!node->visited()) {
			node->set_visited();
			std::vector<std::shared_ptr<Node>> neighbours = g.get_neighbours(node);
			for (std::vector<std::shared_ptr<Node>>::const_iterator it = neighbours.cbegin(); 
				it != neighbours.cend(); 
				++it) {
				dfs(*it, g);
			}
		}
	}
};

class Traverser
{
public:
	Traverser(Traversion* pimpl_, Graph* g_) : pimpl(pimpl_), g(g_) {}
	~Traverser() { }//delete pimpl; }

	void traverse() {
		pimpl->traverse(*g);
	}
private:
	std::shared_ptr<Traversion> pimpl;
	std::shared_ptr<Graph> g;
};

template<>
static void Traverser_::traverse<DFS_Traversion>(const Graph & g)
{
	std::shared_ptr<Node> first_node = g.get_first_node();
	DFS_Traversion::dfs(first_node, g);
}

template<>
static void Traverser_::traverse<BFS_Traversion>(const Graph & g)
{
	std::shared_ptr<Node> first_node = g.get_first_node();
	BFS_Traversion::bfs(first_node, g);
}*/

class Traverser;

class Strategy {
public:
	virtual ~Strategy() = 0;
	void set_traverser(std::shared_ptr<Traverser> tr_) { tr = tr_; }
	virtual void go(const Graph&, const Traverser&) = 0; /*стратегия обхода, переопределяется в наследниках. */
private:
	std::shared_ptr<Traverser> tr;
};

class DFS_Strategy : public Strategy
{

public:
	virtual void go(const Graph& g, const Traverser&) override {
		/*if (!node->visited()) {
			node->set_visited();
			std::vector<std::shared_ptr<Node>> neighbours = g.get_neighbours(node);
			for (std::vector<std::shared_ptr<Node>>::const_iterator it = neighbours.cbegin();
				it != neighbours.cend();
				++it) {
				dfs(*it, g);
			}
		}*/
	}
};

