#ifndef CUCKOO_TABLE_ITERS_HPP
#define CUCKOO_TABLE_ITERS_HPP

#include <cstddef>
#include <utility>
#include "../common/Vector.hpp"
#include "cuckooEntry.hpp"

namespace karpovich
{
  template< class Key, class Value, class Hash1, class Hash2, class Equal >
  class CuckooTable;
  template< class Key, class Value, class Hash1, class Hash2, class Equal >
  class CuckooIter;
  template< class Key, class Value, class Hash1, class Hash2, class Equal >
  class CuckooConstIter;

  template< class Key, class Value, class Hash1, class Hash2, class Equal >
  class CuckooIter
  {
    friend class CuckooTable< Key, Value, Hash1, Hash2, Equal >;
    friend class CuckooConstIter< Key, Value, Hash1, Hash2, Equal >;
    using valType = std::pair< Key, Value >;
    using entryType = details::CuckooEntry< Key, Value >;

  public:
    CuckooIter();
    CuckooIter(Vector< entryType > *table1, Vector< entryType > *table2, size_t capacity, size_t tableIdx, size_t idx);
    CuckooIter &operator++();
    CuckooIter operator++(int);
    bool operator==(const CuckooIter &other) const;
    bool operator!=(const CuckooIter &other) const;
    valType &operator*() const;
    valType *operator->() const;

  private:
    Vector< entryType > *table1_;
    Vector< entryType > *table2_;
    size_t capacity_;
    size_t tableIdx_;
    size_t idx_;
    void findValid();
  };

  template< class Key, class Value, class Hash1, class Hash2, class Equal >
  class CuckooConstIter
  {
    friend class CuckooTable< Key, Value, Hash1, Hash2, Equal >;
    friend class CuckooIter< Key, Value, Hash1, Hash2, Equal >;

    using valType = std::pair< Key, Value >;
    using entryType = details::CuckooEntry< Key, Value >;

  public:
    CuckooConstIter();
    CuckooConstIter(const Vector< entryType > *table1, const Vector< entryType > *table2, size_t capacity,
                    size_t tableIdx, size_t idx);
    CuckooConstIter &operator++();
    CuckooConstIter operator++(int);
    bool operator==(const CuckooConstIter &other) const;
    bool operator!=(const CuckooConstIter &other) const;
    const valType &operator*() const;
    const valType *operator->() const;
  private:
    const Vector< entryType > *table1_;
    const Vector< entryType > *table2_;
    size_t capacity_;
    size_t tableIdx_;
    size_t idx_;
    void findValid();
  };
}

