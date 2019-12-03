#pragma once
#include <memory>
#include "Graph.h"

class Strategy;

class Traverser {
public:
	virtual ~Traverser() {};
	virtual void begin() {}; //можно переопределить, можно и нет, по желанию, мысль такая
	virtual void end() {};
	
	virtual void visit_node(const Node&) = 0; //посещ узла
	virtual void visit_edge(const Edge&) = 0; //посещ ребра 

	void set_strategy(const std::shared_ptr<Strategy>& strat_);
	void set_graph(const std::shared_ptr<Graph>& graph_);

	void graph_begin(); /*нет смысла добавлять поля Graph во всех наследниках. Идея, что
						Traverser будет классом протоколом, в наследниках эти поля уже не нужны, а работа
						в наследниках через интерфейс базового класса - добавление графа, вызов Graph::begin() и.т.п.*/
	void graph_end();

	void traverse(); 

private:
	std::shared_ptr<Strategy> strat{};
	std::shared_ptr<Graph> graph{};
};

class ConcreteTraverser : public Traverser {
public:
	ConcreteTraverser() = default;
	~ConcreteTraverser() = default;
		
	virtual void begin() override;
	virtual void end() override;
	virtual void visit_node(const Node&) override {}; //посещ узла
	virtual void visit_edge(const Edge&) override {}; //посещ ребра 
};