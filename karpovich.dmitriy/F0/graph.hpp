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

  template< class T >
  Graph< T >::Graph():
    vertices_()
  {}

  template< class T >
  size_t Graph< T >::addVertex(const T &value)
  {
    vertices_.pushBack(detail::Vertex< T >(value));
    return vertices_.getSize() - 1;
  }

  template< class T >
  void Graph< T >::addEdge(size_t from, size_t to, const std::string &label)
  {
    if (from >= vertices_.getSize() || to >= vertices_.getSize()) {
      return;
    }
    vertices_[from].edges_.pushBack(detail::Edge< T >(to, label));
  }
}

#endif
