#include "pch.h"
#include <iostream>

#include "Traverser.h"
#include "Graph.h"
#include "MyGraph.h"
#include "Strategy.h"

int main()
{
	size_t size = 1;
	std::shared_ptr<MyGraph> g (new MyGraph(1));
	int a = 5;
	
	std::shared_ptr<DFS_Strategy> strat (new DFS_Strategy);
	ConcreteTraverser tr;
	tr.set_strategy(strat);
	tr.set_graph(g);
	tr.traverse();
    std::cout << "Hello World!\n"; 
}

