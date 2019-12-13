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
	std::vector<raw_data> raw
	{
		{1, 1, {}},
		{2, 2, {1}},
	};

	auto g = std::make_shared<MyGraph>(raw);
	auto strat = std::make_shared<DFS_Strategy>();
	auto tr = std::make_shared<EmptyTraverser>();
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();
	EXPECT_TRUE(g->all_visited());

}

TEST(DFS, three_connected_nodes_cycle) {

	std::vector<raw_data> raw
	{
		{1, 1, {}},
		{2, 2, {1}},
		{3, 3, {1, 2}}
	};
	auto g = std::make_shared<MyGraph>(raw);
	auto strat = std::make_shared<DFS_Strategy>();
	auto tr = std::make_shared<TestTraverser>();
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ 1, 2, 3 };
	std::vector<Edge> edge_expect{ {1, 2}, {2, 3} };
	EXPECT_TRUE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));
			
}

TEST(DFS, three_connected_nodes_linear) {
	std::vector<raw_data> raw
	{
		{1, 1, {}},
		{2, 2, {1}},
		{3, 3, {2}}
	};
	auto g = std::make_shared<MyGraph>(raw);
	auto strat = std::make_shared<DFS_Strategy>();
	auto tr = std::make_shared<TestTraverser>();
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ 1, 2, 3 };
	std::vector<Edge> edge_expect{ {1, 2}, {2, 3} };
	EXPECT_TRUE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));
	   	
}

TEST(BFS, two_connected_nodes) {
	std::vector<raw_data> raw
	{
		{1, 1, {}},
		{2, 2, {1}},
	};

	auto g = std::make_shared<MyGraph>(raw);
	auto strat = std::make_shared<BFS_Strategy>();
	auto tr = std::make_shared<EmptyTraverser>();
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();
	EXPECT_TRUE(g->all_visited());
		
}

TEST(BFS, three_connected_nodes_cycle) {

	std::vector<raw_data> raw
	{
		{1, 1, {}},
		{2, 2, {1}},
		{3, 3, {1, 2}}
	};
	auto g = std::make_shared<MyGraph>(raw);

	auto strat = std::make_shared<BFS_Strategy>();
	auto tr = std::make_shared<TestTraverser>();
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ 1, 2, 3 };
	std::vector<Edge> edge_expect{ {1, 2}, {1, 3} };
	EXPECT_TRUE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));
		
}

TEST(BFS, three_connected_nodes_linear) {

	std::vector<raw_data> raw
	{
		{1, 1, {}},
		{2, 2, {1}},
		{3, 3, {2}}
	};
	auto g = std::make_shared<MyGraph>(raw);

	auto strat = std::make_shared<BFS_Strategy>();
	auto tr = std::make_shared<TestTraverser>();
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ 1, 2, 3 };
	std::vector<Edge> edge_expect{ {1, 2}, {2, 3} };
	EXPECT_TRUE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));

}


TEST(DFS, tree_structure) {
	std::vector<raw_data> raw
	{
		{0, 0, {}}, /*голова*/
		{1, 1, {0}},/*к голове*/
		{2, 2, {0}},
		{3, 3, {1}},/*две ветки от первой вершины*/
		{4, 4, {1}},
		{5, 5, {2}},/*две ветки от второй вершины*/
		{6, 6, {2}}
	};
	auto g = std::make_shared<MyGraph>(raw);

	auto strat = std::make_shared<DFS_Strategy>();
	auto tr = std::make_shared<TestTraverser>();
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ 0, 1, 3, 4, 2, 5, 6 };
	std::vector<Edge> edge_expect{ {0, 1}, {1, 3}, {1, 4}, {0, 2}, {2, 5}, {2, 6} };
	EXPECT_TRUE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));

}

TEST(BFS, tree_structure) {

	std::vector<raw_data> raw
	{
		{0, 0, {}}, /*голова*/
		{1, 1, {0}},/*к голове*/
		{2, 2, {0}},
		{3, 3, {1}},/*две ветки от первой вершины*/
		{4, 4, {1}},
		{5, 5, {2}},/*две ветки от второй вершины*/
		{6, 6, {2}}
	};
	auto g = std::make_shared<MyGraph>(raw);

	auto strat = std::make_shared<BFS_Strategy>();
	auto tr = std::make_shared<TestTraverser>();
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ 0, 1, 2, 3, 4, 5, 6 };
	std::vector<Edge> edge_expect{ {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6} };
	EXPECT_TRUE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));
		
}

TEST(BFS, tree_structure_specific_search) {
	std::vector<raw_data> raw
	{
		{0, 0, {}}, /*голова*/
		{1, 1, {0}},/*к голове*/
		{2, 2, {0}},
		{3, 3, {1}},/*две ветки от первой вершины*/
		{4, 4, {1}},
		{5, 5, {2}},/*две ветки от второй вершины*/
		{6, 6, {2}}
	};
	auto g = std::make_shared<MyGraph>(raw);

	auto strat = std::make_shared<BFS_Strategy>();
	int data_to_find = 4;
	auto tr = std::make_shared<SpecificFindTraverser>(data_to_find);
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ 0, 1, 2, 3, 4 /*,id5 , id6*/ };
	std::vector<Edge> edge_expect{ {0, 1}, {0, 2}, {1, 3} /*, {id1, id4} , {id2, id5}, {id2, id6}*/ };
	EXPECT_FALSE(g->all_visited());
	EXPECT_TRUE(tr->nodes_match(expect));
	EXPECT_TRUE(tr->edges_match(edge_expect));

}

TEST(DFS, tree_structure_specific_search) {

	std::vector<raw_data> raw
	{
		{0, 0, {}}, /*голова*/
		{1, 1, {0}},/*к голове*/
		{2, 2, {0}},
		{3, 3, {1}},/*две ветки от первой вершины*/
		{4, 4, {1}},
		{5, 5, {2}},/*две ветки от второй вершины*/
		{6, 6, {2}}
	};
	auto g = std::make_shared<MyGraph>(raw);

	auto strat = std::make_shared<DFS_Strategy>();
	int data_to_find = 4;
	auto tr = std::make_shared<SpecificFindTraverser>(data_to_find);
	strat->set_traverser(tr);
	tr->set_strategy(strat);
	tr->set_graph(g);
	tr->traverse();

	std::vector<NodeID> expect{ 0, 1, 3, 4 /*, id2, id5, id6*/ };
	std::vector<Edge> edge_expect{ {0, 1}, {1, 3}, {1, 4} /* , {id0, id2}, {id2, id5}, {id2, id6}*/ };
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