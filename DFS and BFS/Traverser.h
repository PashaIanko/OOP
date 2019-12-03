#pragma once
#include <memory>
#include "Graph.h"

class Strategy;

class Traverser {
public:
	virtual ~Traverser() {};
	virtual void begin() {}; //����� ��������������, ����� � ���, �� �������, ����� �����
	virtual void end() {};
	
	virtual void visit_node(const Node&) = 0; //����� ����
	virtual void visit_edge(const Edge&) = 0; //����� ����� 

	void set_strategy(const std::shared_ptr<Strategy>& strat_);
	void set_graph(const std::shared_ptr<Graph>& graph_);

	void graph_begin(); /*��� ������ ��������� ���� Graph �� ���� �����������. ����, ���
						Traverser ����� ������� ����������, � ����������� ��� ���� ��� �� �����, � ������
						� ����������� ����� ��������� �������� ������ - ���������� �����, ����� Graph::begin() �.�.�.*/
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
	virtual void visit_node(const Node&) override {}; //����� ����
	virtual void visit_edge(const Edge&) override {}; //����� ����� 
};