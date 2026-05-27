#include <boost/test/unit_test.hpp>
#include "graph.hpp"

using namespace karpovich;

BOOST_AUTO_TEST_SUITE(GraphMethodsTests)

BOOST_AUTO_TEST_CASE(test_default_constructor)
{
  Graph< std::string > graph;

  BOOST_CHECK(graph.empty());
  BOOST_CHECK_EQUAL(graph.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_add_vertex)
{
  Graph< std::string > graph;

  size_t index = graph.addVertex("A");

  BOOST_CHECK_EQUAL(index, 0);
  BOOST_CHECK_EQUAL(graph.size(), 1);
  BOOST_CHECK(!graph.empty());
}

BOOST_AUTO_TEST_CASE(test_has_vertex)
{
  Graph< std::string > graph;

  graph.addVertex("A");

  BOOST_CHECK(graph.hasVertex("A"));
  BOOST_CHECK(!graph.hasVertex("B"));
}

BOOST_AUTO_TEST_CASE(test_find_vertex)
{
  Graph< std::string > graph;

  graph.addVertex("A");
  graph.addVertex("B");

  std::pair< bool, size_t > result = graph.findVertex("B");

  BOOST_CHECK(result.first);
  BOOST_CHECK_EQUAL(result.second, 1);
}

BOOST_AUTO_TEST_CASE(test_find_missing_vertex)
{
  Graph< std::string > graph;

  graph.addVertex("A");

  std::pair< bool, size_t > result = graph.findVertex("Z");

  BOOST_CHECK(!result.first);
}

BOOST_AUTO_TEST_CASE(test_get_vertex)
{
  Graph< std::string > graph;

  graph.addVertex("Start");

  BOOST_CHECK_EQUAL(graph.getVertex(0).data_, "Start");
}

BOOST_AUTO_TEST_CASE(test_add_edge)
{
  Graph< std::string > graph;

  graph.addVertex("A");
  graph.addVertex("B");

  graph.addEdge(0, 1, "to_B");

  const List< detail::Edge< std::string > > &edges = graph.getEdges(0);

  BOOST_CHECK(!edges.empty());

  LCIter< detail::Edge< std::string > > it = edges.begin();

  BOOST_CHECK_EQUAL((*it).to_, 1);
  BOOST_CHECK_EQUAL((*it).label_, "to_B");
}

BOOST_AUTO_TEST_CASE(test_remove_edge)
{
  Graph< std::string > graph;

  graph.addVertex("A");
  graph.addVertex("B");

  graph.addEdge(0, 1, "edge");

  BOOST_CHECK(!graph.getEdges(0).empty());

  graph.removeEdge(0, 1);

  BOOST_CHECK(graph.getEdges(0).empty());
}

BOOST_AUTO_TEST_CASE(test_remove_vertex)
{
  Graph< std::string > graph;

  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");

  BOOST_CHECK_EQUAL(graph.size(), 3);

  graph.removeVertex(1);

  BOOST_CHECK_EQUAL(graph.size(), 2);

  BOOST_CHECK(graph.hasVertex("A"));
  BOOST_CHECK(graph.hasVertex("C"));
  BOOST_CHECK(!graph.hasVertex("B"));
}

BOOST_AUTO_TEST_CASE(test_multiple_edges)
{
  Graph< std::string > graph;

  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");

  graph.addEdge(0, 1, "A_B");
  graph.addEdge(0, 2, "A_C");

  const List< detail::Edge< std::string > > &edges = graph.getEdges(0);

  BOOST_CHECK_EQUAL(edges.size(), 2);
}

BOOST_AUTO_TEST_SUITE_END()
