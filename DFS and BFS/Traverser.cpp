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
	graph_begin(); //��� �� ���������� ������������, �.�. �� ����� ������������� ���� �����, � ��� ��� �������������
}

void EmptyTraverser::end() {
	graph_end();
}

bool TestTraverser::visit_node(const Node & n) {
	nodes_sequence.push_back(n.get_id());
	return false;
}

bool TestTraverser::visit_edge(const Edge & e) {
	edges_sequence.push_back(e);
	return false;
}

bool TestTraverser::nodes_match(const std::vector<NodeID> v) const
{
	return nodes_sequence == v;
}

bool TestTraverser::edges_match(const std::vector<Edge> v) const
{
	return edges_sequence == v;
}

bool SpecificFindTraverser::visit_node(const Node & n)
{
	nodes_sequence.push_back(n.get_id());
	return n.get_data() == data_to_find;
}

bool SpecificFindTraverser::visit_edge(const Edge & e) {
	edges_sequence.push_back(e);
	return false;
}

bool SpecificFindTraverser::nodes_match(const std::vector<NodeID> v) const
{
	return v == nodes_sequence;
}

bool SpecificFindTraverser::edges_match(const std::vector<Edge> v) const
{
	return v == edges_sequence;
}
