#pragma once
#include <memory>
#include "Strategy.h"

class Strategy;

class Traverser {
public:
	virtual ~Traverser() {};
	virtual void begin() = 0;
	virtual void end() = 0;
	virtual void visit_node(const Node&) = 0; //посещ узла
	virtual void visit_edge(const Edge&) = 0; //посещ ребра 

	void set_strategy(const std::shared_ptr<Strategy>& strat_) { strat = strat_; };
	void set_graph(const std::shared_ptr<Graph>& graph_) { graph = graph_; };

	void traverse() {
		strat->go(*graph);// , *this);/*обход графа g, со ссылкой на абстрактный базовый
							//класс Traverser. ћетоды посещени€ переопредел€тс€ в наследниках Traverser'a*/
	}

private:
	std::shared_ptr<Strategy> strat{};
	std::shared_ptr<Graph> graph{};
};

class ConcreteTraverser : public Traverser {
public:
	ConcreteTraverser() = default;
	~ConcreteTraverser() = default;
		
	virtual void begin() override {};
	virtual void end() override {};
	virtual void visit_node(const Node&) override {}; //посещ узла
	virtual void visit_edge(const Edge&) override {}; //посещ ребра 
};