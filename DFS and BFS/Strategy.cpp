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

void DFS_Strategy::go(Graph & g, std::shared_ptr<Node> start_node) {
	traverser_begin();
	//std::shared_ptr<Node> node = g.get_first_node();
	dfs(g, start_node);
}

void DFS_Strategy::dfs(Graph & g, std::shared_ptr<Node>& node) {
	if (!node->visited()) {
		traverser_visit_node(*node);
		node->set_visited();
		
		for (std::vector<std::shared_ptr<Node>>::iterator it = node->neighbours_begin();
			it != node->neighbours_end();
			++it) {
			if (!(*it)->visited()) {
				Edge edge(node, *it);
				//std::shared_ptr<Edge> edge = g.get_edge(*node, *(*it));
				/*конструируем едже по двум нодам --> visit_edge*/
				traverser_visit_edge(edge);
				dfs(g, *(it));
			}
		}
	}
}

void BFS_Strategy::go(Graph & g, std::shared_ptr<Node> start_node) {
	traverser_begin();
	bfs(g, start_node);
}

void BFS_Strategy::bfs(Graph & g, std::shared_ptr<Node>& node) {
	if (!node->visited()) {
		traverser_visit_node(*node);
		node->set_visited();
	}
	for (auto it = node->neighbours_begin(); it != node->neighbours_end(); ++it) {
		if (!(*it)->visited()) {
			traverser_visit_node(*(*it));
			(*it)->set_visited();

			Edge edge(node, *it);
			traverser_visit_edge(edge);

			nodes_stack.push_back(*it);
		}
	}
	/*рекурсивно перезапуск процедуры с указателем Node на ноду в верхушке стека
	предварительно убрав этот элемент из стека*/
	if (!nodes_stack.empty()) {
		std::shared_ptr<Node> temp_node = nodes_stack.front();
		nodes_stack.pop_front();
		bfs(g, temp_node);
	}
	
}
