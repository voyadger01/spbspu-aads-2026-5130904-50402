#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <Vector.hpp>
#include <list.hpp>
#include <string>
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
    std::pair< bool, size_t > findVertex(const T &value) const;
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
    vertices_[from].edges_.push_back(detail::Edge< T >(to, label));
  }

  template< class T >
  void Graph< T >::removeEdge(size_t from, size_t to)
  {
    if (from >= vertices_.getSize()) {
      return;
    }
    List< detail::Edge< T > > &edges = vertices_[from].edges_;
    LIter< detail::Edge< T > > it = edges.begin();
    while (it != edges.end()) {
      if ((*it).to_ == to) {
        it = edges.erase(it);
      } else {
        ++it;
      }
    }
  }

  template< class T >
  void Graph< T >::removeVertex(size_t index)
  {
    if (index >= vertices_.getSize()) {
      throw std::out_of_range("Invalid vertex index");
    }
    vertices_.erase(vertices_.begin() + index);
    for (size_t i = 0; i < vertices_.getSize(); ++i) {
      List< detail::Edge< T > > &edges = vertices_[i].edges_;
      LIter< detail::Edge< T > > it = edges.begin();
      while (it != edges.end()) {
        if ((*it).to_ == index) {
          it = edges.erase(it);
        } else {
          if ((*it).to_ > index) {
            (*it).to_--;
          }
          ++it;
        }
      }
    }
  }
  template< class T >
  bool Graph< T >::hasVertex(const T &value) const
  {
    return findVertex(value).first;
  }

  template< class T >
  std::pair< bool, size_t > Graph< T >::findVertex(const T &value) const
  {
    for (size_t i = 0; i < vertices_.getSize(); ++i) {
      if (vertices_[i].data_ == value) {
        return std::make_pair(true, i);
      }
    }
    return std::make_pair(false, 0);
  }

  template< class T >
  detail::Vertex< T > &Graph< T >::getVertex(size_t index)
  {
    return vertices_[index];
  }

  template< class T >
  const detail::Vertex< T > &Graph< T >::getVertex(size_t index) const
  {
    return vertices_[index];
  }

  template< class T >
  List< detail::Edge< T > > &Graph< T >::getEdges(size_t index)
  {
    return vertices_[index].edges_;
  }

  template< class T >
  const List< detail::Edge< T > > &Graph< T >::getEdges(size_t index) const
  {
    return vertices_[index].edges_;
  }

  template< class T >
  size_t Graph< T >::size() const
  {
    return vertices_.getSize();
  }

  template< class T >
  bool Graph< T >::empty() const
  {
    return vertices_.isEmpty();
  }

}

#endif
