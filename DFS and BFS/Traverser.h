#pragma once
#include <memory>
#include "Strategy.h"


class Traverser {
public:
	virtual ~Traverser() = 0;
	virtual void begin() = 0;
	virtual void end() = 0;
	virtual void visit_node() = 0; //����� ����
	virtual void visit_edge() = 0; //����� ����� 

	void set_strategy(const std::shared_ptr<Strategy>& strat_) { strat = strat_; };
	void traverse(Graph&g) {
		strat->go(g, *this);/*����� ����� g, �� ������� �� ����������� �������
							����� Traverser. ������ ��������� ��������������� � ����������� Traverser'a*/
	}

private:
	std::shared_ptr<Strategy> strat{};
};