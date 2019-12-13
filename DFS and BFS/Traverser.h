#pragma once
#include <memory>
#include "Graph.h"

class Strategy;

class Traverser {
public:
	virtual ~Traverser() {};
	virtual void begin() {}; //����� ��������������, ����� � ���, �� �������, ����� �����
	virtual void end() {};
	
	virtual bool visit_node(const Node&) = 0; //����� ���� - ���� true ������� - �����, ��� ������
	virtual bool visit_edge(const Edge&) = 0; //����� ����� 

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
	virtual bool visit_node(const Node&) override { return false; }; //����� ����
	virtual bool visit_edge(const Edge&) override { return false; }; //����� ����� 
};

class TestTraverser : public Traverser {
public:
	TestTraverser() = default;
	~TestTraverser() = default;

	virtual void begin() override {};
	virtual void end() override {};
	virtual bool visit_node(const Node&) override; //����� ����
	virtual bool visit_edge(const Edge&) override; //����� ����� 

	bool nodes_match(const std::vector<NodeID> v) const;
	bool edges_match(const std::vector<Edge> v) const;

private:
	/*������ ������ Node Id, ���� ���������� ����
	���������� ���. � ������, � ������, ���������� � ��������� �����
	��������������*/
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
	virtual bool visit_node(const Node&) override; //����� ����
	virtual bool visit_edge(const Edge&) override; //����� ����� 

	bool nodes_match(const std::vector<NodeID> v) const;
	bool edges_match(const std::vector<Edge> v) const;

private:
	std::vector<NodeID> nodes_sequence{};
	std::vector <Edge> edges_sequence{};
	int data_to_find{};

};