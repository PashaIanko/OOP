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

bool Strategy::traverser_visit_node(Node & node) {
	auto shared_traverser = traverser.lock();
	if (shared_traverser != nullptr) {
		return shared_traverser->visit_node(node);
	}
	return false;
}

bool Strategy::traverser_visit_edge(Edge& edge) {
	auto shared_traverser = traverser.lock();
	if (shared_traverser != nullptr) {
		return shared_traverser->visit_edge(edge);
	}
	return false;
}

void DFS_Strategy::go(Graph & g, std::shared_ptr<Node> start_node) {
	traverser_begin();
	dfs(g, start_node.get());
}

void DFS_Strategy::dfs(Graph & g, Node* node) {
	if (have_to_exit)
		return;

	if (!node->visited()) {

		bool visit_node_res = traverser_visit_node(*node);
		node->set_visited();
		
		if (visit_node_res) {
			have_to_exit = true;
			return;
		}

		for (std::vector<Node*>::iterator it = node->neighbours_begin();
			it != node->neighbours_end();
			++it) {

			if (have_to_exit)
				return; /*выходы из рекурсий как метод посещения нашёл то что нужно*/

			if (!(*it)->visited()) {
				Edge edge(node, *it);
				if (traverser_visit_edge(edge))
					return;
				else {
					dfs(g, *(it)); /*если не нашли ни в вершине ни в ребре, продолжаем поиск*/
				}
			}
		}
	}
}

void BFS_Strategy::go(Graph & g, std::shared_ptr<Node> start_node) {
	traverser_begin();
	bfs(g, start_node.get());
}

void BFS_Strategy::bfs(Graph & g, Node* node) {

	bool visit_node_res = false;
	if (!node->visited()) {
		visit_node_res = traverser_visit_node(*node);
		node->set_visited();
	}

	if (visit_node_res) {
		have_to_exit = true;
		return;
	}

	for (std::vector<Node*>::iterator it = node->neighbours_begin(); it != node->neighbours_end(); ++it) {

		if (have_to_exit)
			return; /*выходы из рекурсий как метод посещения нашёл то что нужно*/

		if (!(*it)->visited()) {
			visit_node_res = traverser_visit_node(*(*it));
			(*it)->set_visited();

			if (visit_node_res)
				return;

			Edge edge(node, *it);

			if (traverser_visit_edge(edge)) /*посещение ребра вернуло true? нашли что хотели с ребром*/
				return;

			nodes_stack.push_back(*it);
		}
	}
	/*рекурсивно перезапуск процедуры с указателем Node на ноду в верхушке стека
	предварительно убрав этот элемент из стека*/
	if (!nodes_stack.empty()) {
		Node* temp_node = nodes_stack.front();
		nodes_stack.pop_front();
		bfs(g, temp_node);
	}
		
	
}
