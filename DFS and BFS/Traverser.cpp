#include "pch.h"
#include "Traverser.h"
#include "Strategy.h"

void Traverser::set_strategy(const std::shared_ptr<Strategy>& strat_) {
	strat = strat_;
}

void Traverser::set_graph(const std::shared_ptr<Graph>& graph_) {
	graph = graph_;
}

void Traverser::graph_begin() {
	graph->begin();
}

void Traverser::graph_end() {
	graph->end();
}

void Traverser::traverse() {
	strat->go(*graph, graph->get_first_node());
}

void EmptyTraverser::begin() {
	graph_begin(); //это не чрезмерна€ инкапсул€ци€, т.е. мы можем переоределить этот метод, € его так переопределил
}

void EmptyTraverser::end() {
	graph_end();
}

void TestTraverser::visit_node(const Node & n) {
	nodes_sequence.push_back(n.get_id());
}

void TestTraverser::visit_edge(const Edge & e) {
	edges_sequence.push_back(e);
}

bool TestTraverser::nodes_match(const std::vector<NodeID> v) const
{
	return nodes_sequence == v;
}

bool TestTraverser::edges_match(const std::vector<Edge> v) const
{
	return edges_sequence == v;
}
