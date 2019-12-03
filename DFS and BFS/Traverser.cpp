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
	strat->go(*graph); // *this);/*����� ����� g, �� ������� �� ����������� �������
							//����� Traverser. ������ ��������� ��������������� � ����������� Traverser'a*/
}

void ConcreteTraverser::begin() {
	graph_begin(); //��� �� ���������� ������������, �.�. �� ����� ������������� ���� �����, � ��� ��� �������������
}

void ConcreteTraverser::end() {
	graph_end();
}
