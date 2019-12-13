#include "pch.h"
#include "gtest\gtest.h"
#include "..\DFS_and_BFS\Edge.h"
#include "..\DFS_and_BFS\Graph.h"
#include "..\DFS_and_BFS\MyGraph.h"
#include "..\DFS_and_BFS\Node.h"
#include "..\DFS_and_BFS\NodeID.h"
#include "..\DFS_and_BFS\Strategy.h"
#include "..\DFS_and_BFS\Traverser.h"

TEST(DFS, two_connected_nodes) {
	std::shared_ptr<MyGraph> g(new MyGraph);
	NodeID id1(1);
	NodeID id2(2);
	Node n1(1, id1);//data, id
	Node n2(2, id2);
	std::vector<NodeID> v{ id1 };
	g->addNode(n1);
	g->addNode(n2, v);

	std::shared_ptr<DFS_Strategy> strat(new DFS_Strategy);
	auto tr = std::make_shared<EmptyTraverser>();
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	EXPECT_TRUE(g->all_visited());
}

TEST(DFS, three_connected_nodes_cycle) {

	/*три ноды в цикле*/

	std::shared_ptr<MyGraph> g(new MyGraph);
	NodeID id1(1);
	NodeID id2(2);
	NodeID id3(3);
	Node n1(1, id1);//data, id
	Node n2(2, id2);
	Node n3(3, id3);

	std::vector<NodeID> v{ id1 }; /*2я вершина соединена с 1ой*/
	std::vector<NodeID> v2{ id1, id2 }; /*3я вершина соединена с 1ой и 2ой*/

	g->addNode(n1);
	g->addNode(n2, v);
	g->addNode(n3, v2);


	std::shared_ptr<DFS_Strategy> strat(new DFS_Strategy);
	std::shared_ptr<TestTraverser> tr(new TestTraverser);
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ id1, id2, id3 };
	std::vector<Edge> edge_expect{ {id1, id2}, {id2, id3} };
	EXPECT_TRUE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));
}

TEST(DFS, three_connected_nodes_linear) {

	/*три ноды линейно 1-2-3*/

	std::shared_ptr<MyGraph> g(new MyGraph);
	NodeID id1(1);
	NodeID id2(2);
	NodeID id3(3);
	Node n1(1, id1);//data, id
	Node n2(2, id2);
	Node n3(3, id3);

	std::vector<NodeID> v{ id1 }; /*2я вершина соединена с 1ой*/
	std::vector<NodeID> v2{ id2 }; /*3я вершина соединена с 1ой и 2ой*/

	g->addNode(n1);
	g->addNode(n2, v);
	g->addNode(n3, v2);


	std::shared_ptr<DFS_Strategy> strat(new DFS_Strategy);
	std::shared_ptr<TestTraverser> tr(new TestTraverser);
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ id1, id2, id3 };
	std::vector<Edge> edge_expect{ {id1, id2}, {id2, id3} };
	EXPECT_TRUE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));
}

TEST(BFS, two_connected_nodes) {
	std::shared_ptr<MyGraph> g(new MyGraph);
	NodeID id1(1);
	NodeID id2(2);
	Node n1(1, id1);//data, id
	Node n2(2, id2);
	std::vector<NodeID> v{ id1 };
	g->addNode(n1);
	g->addNode(n2, v);

	std::shared_ptr<BFS_Strategy> strat(new BFS_Strategy);
	std::shared_ptr<EmptyTraverser> tr(new EmptyTraverser);
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();
	EXPECT_TRUE(g->all_visited());
}

TEST(BFS, three_connected_nodes_cycle) {

	/*три ноды в цикле*/

	std::shared_ptr<MyGraph> g(new MyGraph);
	NodeID id1(1);
	NodeID id2(2);
	NodeID id3(3);
	Node n1(1, id1);//data, id
	Node n2(2, id2);
	Node n3(3, id3);

	std::vector<NodeID> v{ id1 }; /*2я вершина соединена с 1ой*/
	std::vector<NodeID> v2{ id1, id2 }; /*3я вершина соединена с 1ой и 2ой*/

	g->addNode(n1);
	g->addNode(n2, v);
	g->addNode(n3, v2);


	std::shared_ptr<BFS_Strategy> strat(new BFS_Strategy);
	std::shared_ptr<TestTraverser> tr(new TestTraverser);
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ id1, id2, id3 };
	std::vector<Edge> edge_expect{ {id1, id2}, {id1, id3} };
	EXPECT_TRUE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));
}

TEST(BFS, three_connected_nodes_linear) {

	/*три ноды линейно 1-2-3*/

	std::shared_ptr<MyGraph> g(new MyGraph);
	NodeID id1(1);
	NodeID id2(2);
	NodeID id3(3);
	Node n1(1, id1);//data, id
	Node n2(2, id2);
	Node n3(3, id3);

	std::vector<NodeID> v{ id1 }; /*2я вершина соединена с 1ой*/
	std::vector<NodeID> v2{ id2 }; /*3я вершина соединена с 1ой и 2ой*/

	g->addNode(n1);
	g->addNode(n2, v);
	g->addNode(n3, v2);


	std::shared_ptr<BFS_Strategy> strat(new BFS_Strategy);
	std::shared_ptr<TestTraverser> tr(new TestTraverser);
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ id1, id2, id3 };
	std::vector<Edge> edge_expect{ {id1, id2}, {id2, id3} };
	EXPECT_TRUE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));
}


TEST(DFS, tree_structure) {

	std::shared_ptr<MyGraph> g(new MyGraph);

	NodeID id0(0);
	NodeID id1(1);
	NodeID id2(2);
	NodeID id3(3);
	NodeID id4(4);
	NodeID id5(5);
	NodeID id6(6);

	Node n0(0, id0);//data, id
	Node n1(1, id1);//data, id
	Node n2(2, id2);
	Node n3(3, id3);
	Node n4(4, id4);
	Node n5(5, id5);
	Node n6(6, id6);

	g->addNode(n0);
	g->addNode(n1, id0); /*подсоединены к голове*/
	g->addNode(n2, id0);

	//ветки
	g->addNode(n3, id1);
	g->addNode(n4, id1);

	//ветки
	g->addNode(n5, id2);
	g->addNode(n6, id2);


	std::shared_ptr<DFS_Strategy> strat(new DFS_Strategy);
	std::shared_ptr<TestTraverser> tr(new TestTraverser);
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ id0, id1, id3, id4, id2, id5, id6 };
	std::vector<Edge> edge_expect{ {id0, id1}, {id1, id3}, {id1, id4}, {id0, id2}, {id2, id5}, {id2, id6} };
	EXPECT_TRUE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));
}

TEST(BFS, tree_structure) {

	std::shared_ptr<MyGraph> g(new MyGraph);

	NodeID id0(0);
	NodeID id1(1);
	NodeID id2(2);
	NodeID id3(3);
	NodeID id4(4);
	NodeID id5(5);
	NodeID id6(6);

	Node n0(0, id0);//data, id
	Node n1(1, id1);//data, id
	Node n2(2, id2);
	Node n3(3, id3);
	Node n4(4, id4);
	Node n5(5, id5);
	Node n6(6, id6);

	g->addNode(n0);
	g->addNode(n1, id0); /*подсоединены к голове*/
	g->addNode(n2, id0);

	//ветки
	g->addNode(n3, id1);
	g->addNode(n4, id1);

	//ветки
	g->addNode(n5, id2);
	g->addNode(n6, id2);


	std::shared_ptr<BFS_Strategy> strat(new BFS_Strategy);
	std::shared_ptr<TestTraverser> tr(new TestTraverser);
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ id0, id1, id2, id3, id4, id5, id6 };
	std::vector<Edge> edge_expect{ {id0, id1}, {id0, id2}, {id1, id3}, {id1, id4}, {id2, id5}, {id2, id6} };
	EXPECT_TRUE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));
}

TEST(BFS, tree_structure_specific_search) {

	/*В этом тесте, ищем по структуре специфические данные, например 
	цифру 4 в четвёртой ноде -- > неполный обход*/

	std::shared_ptr<MyGraph> g(new MyGraph);

	NodeID id0(0);
	NodeID id1(1);
	NodeID id2(2);
	NodeID id3(3);
	NodeID id4(4);
	NodeID id5(5);
	NodeID id6(6);

	Node n0(0, id0);//data, id
	Node n1(1, id1);//data, id
	Node n2(2, id2);
	Node n3(3, id3);
	Node n4(4, id4);
	Node n5(5, id5);
	Node n6(6, id6);

	g->addNode(n0);
	g->addNode(n1, id0); /*подсоединены к голове*/
	g->addNode(n2, id0);

	//ветки
	g->addNode(n3, id1);
	g->addNode(n4, id1);

	//ветки
	g->addNode(n5, id2);
	g->addNode(n6, id2);


	std::shared_ptr<BFS_Strategy> strat(new BFS_Strategy);
	int data_to_find = 4;
	std::shared_ptr<SpecificFindTraverser> tr(new SpecificFindTraverser(data_to_find));
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ id0, id1, id2, id3, id4 /*,id5 , id6*/ };
	std::vector<Edge> edge_expect{ {id0, id1}, {id0, id2}, {id1, id3} /*, {id1, id4} , {id2, id5}, {id2, id6}*/ };
	EXPECT_FALSE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));
}

TEST(DFS, tree_structure_specific_search) {

	/*В этом тесте, ищем по структуре специфические данные, например
	цифру 4 в четвёртой ноде -- > неполный обход*/

	std::shared_ptr<MyGraph> g(new MyGraph);

	NodeID id0(0);
	NodeID id1(1);
	NodeID id2(2);
	NodeID id3(3);
	NodeID id4(4);
	NodeID id5(5);
	NodeID id6(6);

	Node n0(0, id0);//data, id
	Node n1(1, id1);//data, id
	Node n2(2, id2);
	Node n3(3, id3);
	Node n4(4, id4);
	Node n5(5, id5);
	Node n6(6, id6);

	g->addNode(n0);
	g->addNode(n1, id0); /*подсоединены к голове*/
	g->addNode(n2, id0);

	//ветки
	g->addNode(n3, id1);
	g->addNode(n4, id1);

	//ветки
	g->addNode(n5, id2);
	g->addNode(n6, id2);


	std::shared_ptr<DFS_Strategy> strat(new DFS_Strategy);
	int data_to_find = 4;
	std::shared_ptr<SpecificFindTraverser> tr(new SpecificFindTraverser(data_to_find));
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ id0, id1, id3, id4 /*, id2, id5, id6*/ };
	std::vector<Edge> edge_expect{ {id0, id1}, {id1, id3}, {id1, id4} /* , {id0, id2}, {id2, id5}, {id2, id6}*/ };
	EXPECT_FALSE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));
}


/*int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}*/