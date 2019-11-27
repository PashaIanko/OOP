#include "pch.h"
#include <iostream>

#include "Graph.h"
#include "MyGraph.h"
#include "Strategy.h"

int main()
{
	size_t size = 1;
	MyGraph g(1);
	int a = 5;
	//g.addNode(a);
	//g.add_node(1);

	Traverser_::traverse<DFS_Traversion>(g);
	Traverser_::traverse<BFS_Traversion>(g);

    std::cout << "Hello World!\n"; 
}

