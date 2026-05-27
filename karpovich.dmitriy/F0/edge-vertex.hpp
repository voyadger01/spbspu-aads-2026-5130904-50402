#ifndef EDGE_VERTEX_HPP
#define EDGE_VERTEX_HPP

#include <cstddef>
#include <string>
#include "../common/list.hpp"

namespace karpovich
{
  namespace detail
  {
    template< class T >
    struct Edge
    {
      size_t to_;
      std::string label_;

      Edge();
      Edge(size_t to, const std::string &label);
    };

    template< class T >
    struct Vertex
    {
      T data_;
      List< Edge< T > > edges_;

      Vertex();
      Vertex(const T &data);
    };

    template< class T >
    Edge< T >::Edge():
      to_(0),
      label_()
    {}

    template< class T >
    Edge< T >::Edge(size_t to, const std::string &label):
      to_(to),
      label_(label)
    {}

    template< class T >
    Vertex< T >::Vertex():
      data_(),
      edges_()
    {}

    template< class T >
    Vertex< T >::Vertex(const T &data):
      data_(data),
      edges_()
    {}
  }
}
#endif
