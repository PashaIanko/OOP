#pragma once
#include <memory>
#include "Graph.h"

class Strategy;

class Traverser {
public:
	virtual ~Traverser() {};
	virtual void begin() {}; //можно переопределить, можно и нет, по желанию, мысль такая
	virtual void end() {};
	
	virtual bool visit_node(const Node&) = 0; //посещ узла - если true вернули - нашли, что хотели
	virtual bool visit_edge(const Edge&) = 0; //посещ ребра 

	void set_strategy(const std::shared_ptr<Strategy>& strat_);
	void set_graph(const std::shared_ptr<Graph>& graph_);

	
	void traverse(); 

protected:
	void graph_begin(); /*нет смысла добавлять поля Graph во всех наследниках. Идея, что
						Traverser будет классом протоколом, в наследниках эти поля уже не нужны, а работа
						в наследниках через интерфейс базового класса - добавление графа, вызов Graph::begin() и.т.п.*/
	void graph_end();

private:
	std::shared_ptr<Strategy> strat{};
	std::shared_ptr<Graph> graph{};
};

class EmptyTraverser : public Traverser {
public:
	EmptyTraverser() = default;
	~EmptyTraverser() = default;

	virtual void begin() override;
	virtual void end() override;
	virtual bool visit_node(const Node&) override { return false; }; //посещ узла
	virtual bool visit_edge(const Edge&) override { return false; }; //посещ ребра 
};

class TestTraverser : public Traverser {
public:
	TestTraverser() = default;
	~TestTraverser() = default;

	virtual void begin() override {};
	virtual void end() override {};
	virtual bool visit_node(const Node&) override; //посещ узла
	virtual bool visit_edge(const Edge&) override; //посещ ребра 

	bool nodes_match(const std::vector<NodeID> v) const;
	bool edges_match(const std::vector<Edge> v) const;

private:
	/*держим вектор Node Id, куда закидываем айди
	посещаемых нод. В наруже, в тестах, сравниваем с ожидаемой после
	довательностью*/
	std::vector<NodeID> nodes_sequence {};
	std::vector <Edge> edges_sequence{};
};

class SpecificFindTraverser : public Traverser {
public:
	SpecificFindTraverser() = delete;
	~SpecificFindTraverser() = default;
	SpecificFindTraverser(int data) : data_to_find(data) {};

	virtual void begin() override {};
	virtual void end() override {};
	virtual bool visit_node(const Node&) override; //посещ узла
	virtual bool visit_edge(const Edge&) override; //посещ ребра 

	bool nodes_match(const std::vector<NodeID> v) const;
	bool edges_match(const std::vector<Edge> v) const;

private:
	std::vector<NodeID> nodes_sequence{};
	std::vector <Edge> edges_sequence{};
	int data_to_find{};

};