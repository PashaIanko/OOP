#pragma once

/*class GraphIterator;

class Graph {

public:
	virtual GraphIterator cbegin() const = 0;
};

class TraverseStrategy {
public:
	virtual ~TraverseStrategy() = 0;

	virtual void traverse(const Graph& g) = 0;

};

class DFSStrategy :public TraverseStrategy {
public:
	virtual ~DFSStrategy() {};
	void traverse(const Graph &g) override {
		dfs(g.cbegin());
	};

private:
	void dfs(const GraphIterator& iterator) {
		if (iterator.get_visited() == false) {
			iterator.set_visited(true);
			for (auto it : iterator.neighbours) {
				dfs(it);
			}
		}
		
	}
};

class Traverser {
public:
	virtual ~Traverser() = 0;
	virtual void begin_tr() = 0;
	virtual void end_tr() = 0;
	virtual void visit_arc() = 0;
	virtual void visit_node() = 0;
};*/

#include <memory>
#include "Graph.h"

class Traversion
{
public:
	virtual ~Traversion() {}
	virtual void traverse(const Graph& ) = 0;
};

class BFS_Traversion : public Traversion
{
public:
	void traverse(const Graph& g) override {
		
	}
};

class DFS_Traversion : public Traversion
{
	
public:
	void traverse(const Graph& g) override {
		for (citerator it = g.cbegin(); it != g.cend(); ++it) {
			dfs(*it); /*либо dfs(iterator), либо dfs(Node*), но по идее класс DFS_Traversion
												не должен ничего знать о полях Node, поэтому от итератора?*/
		}
	}

private:
	void dfs(const citerator& it) {
		it.set_visited();
		for (auto it_ : it.neighbours) {
			/*citerator 
			dfs(it_);*/
			/*А тут что? Конструируем итератор по каждому элементу Node* и вызываем метод dfs(сконстр. итератор)?*/
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
