#include "pch.h"
#include <iostream>

#include "Traverser.h"
#include "Graph.h"
#include "MyGraph.h"
#include "Strategy.h"

int main()
{
	size_t size = 1;
	std::shared_ptr<MyGraph> g (new MyGraph);
	MyNode my_node(5, 1); 
	std::vector<NodeID> v{};
	g->addNode(my_node, v);
	int a = 5;
	
	std::shared_ptr<DFS_Strategy> strat (new DFS_Strategy);
	std::shared_ptr<ConcreteTraverser> tr (new ConcreteTraverser);

	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();
    std::cout << "Hello World!\n"; 
}

