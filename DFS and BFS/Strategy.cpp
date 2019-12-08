#include "pch.h"
#include "Strategy.h"
#include "Traverser.h"

void Strategy::set_traverser(std::shared_ptr<Traverser> traverser_) {
	traverser = traverser_;
}

void Strategy::traverser_begin(){
	auto shared_traverser = traverser.lock();
	if (shared_traverser != nullptr) {
		shared_traverser->begin();
	}
}

void Strategy::traverser_visit_node(Node & node) {
	auto shared_traverser = traverser.lock();
	if (shared_traverser != nullptr) {
		shared_traverser->visit_node(node);
	}
}

void Strategy::traverser_visit_edge(Edge& edge) {
	auto shared_traverser = traverser.lock();
	if (shared_traverser != nullptr) {
		shared_traverser->visit_edge(edge);
	}
}

void DFS_Strategy::go(Graph & g) {
	traverser_begin();
	std::shared_ptr<Node> node = g.get_first_node();
	dfs(g, node);
}

void DFS_Strategy::dfs(Graph & g, std::shared_ptr<Node>& node) {
	if (!node->visited()) {
		traverser_visit_node(*node);
		node->set_visited();
		
		for (std::vector<std::shared_ptr<Node>>::iterator it = node->neighbours_begin();
			it != node->neighbours_end();
			++it) {
			
			std::shared_ptr<Edge> edge = g.get_edge(*node, *(*it));
			/*конструируем едже по двум нодам --> visit_edge*/
			traverser_visit_edge(*edge);
			dfs(g, *(it));
		}
	}
}
