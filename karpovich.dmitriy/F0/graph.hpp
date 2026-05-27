#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include "../common/Vector.hpp"
#include "../common/list.hpp"
#include "edge-vertex.hpp"
namespace karpovich
{
  template< class T >
  class Graph
  {
  public:
    Graph();

    size_t addVertex(const T &value);
    void addEdge(size_t from, size_t to, const std::string &label = "");
    void removeEdge(size_t from, size_t to);
    void removeVertex(size_t index);
    bool hasVertex(const T &value) const;
    size_t findVertex(const T &value) const;
    detail::Vertex< T > &getVertex(size_t index);
    const detail::Vertex< T > &getVertex(size_t index) const;
    List< detail::Edge< T > > &getEdges(size_t index);
    const List< detail::Edge< T > > &getEdges(size_t index) const;
    size_t size() const;
    bool empty() const;
  private:
    Vector< detail::Vertex< T > > vertices_;
  };
}

#endif
