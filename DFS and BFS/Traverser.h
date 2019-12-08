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

	
	void traverse(); 

protected:
	void graph_begin(); /*��� ������ ��������� ���� Graph �� ���� �����������. ����, ���
						Traverser ����� ������� ����������, � ����������� ��� ���� ��� �� �����, � ������
						� ����������� ����� ��������� �������� ������ - ���������� �����, ����� Graph::begin() �.�.�.*/
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
	virtual void visit_node(const Node&) override {}; //����� ����
	virtual void visit_edge(const Edge&) override {}; //����� ����� 
};

class TestTraverser : public Traverser {
public:
	TestTraverser() = default;
	~TestTraverser() = default;

	virtual void begin() override {};
	virtual void end() override {};
	virtual void visit_node(const Node&) override; //����� ����
	virtual void visit_edge(const Edge&) override; //����� ����� 

	bool nodes_match(const std::vector<NodeID> v) const;
	bool edges_match(const std::vector<Edge> v) const;

private:
	/*������ ������ Node Id, ���� ���������� ����
	���������� ���. � ������, � ������, ���������� � ��������� �����
	��������������*/
	std::vector<NodeID> nodes_sequence {};
	std::vector <Edge> edges_sequence{};
};