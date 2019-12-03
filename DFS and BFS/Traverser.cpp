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
	strat->go(*graph); // *this);/*обход графа g, со ссылкой на абстрактный базовый
							//класс Traverser. ћетоды посещени€ переопредел€тс€ в наследниках Traverser'a*/
}

void ConcreteTraverser::begin() {
	graph_begin(); //это не чрезмерна€ инкапсул€ци€, т.е. мы можем переоределить этот метод, € его так переопределил
}

void ConcreteTraverser::end() {
	graph_end();
}
