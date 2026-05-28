#ifndef CUCKOO_TABLE_HPP
#define CUCKOO_TABLE_HPP

#include <cstddef>
#include <functional>
#include <utility>
#include "../common/Vector.hpp"
#include "../common/hashFunctions.hpp"
#include "cuckooEntry.hpp"

namespace karpovich
{
  template< class T >
  using eq = std::equal_to< T >;
  template< class T >
  using hash = PairHasher< T >;
  template< class Key, class Value, class Hash1 = hash< Key >, class Hash2 = std::hash< Key >, class Equal = eq< Key > >
  class CuckooTable
  {
  public:
    using valType = std::pair< Key, Value >;
    using entryType = details::CuckooEntry< Key, Value >;

    explicit CuckooTable(size_t capacity = 16);
    ~CuckooTable();

    CuckooTable(const CuckooTable &other);
    CuckooTable(CuckooTable &&other) noexcept;
    CuckooTable &operator=(const CuckooTable &other);
    CuckooTable &operator=(CuckooTable &&other) noexcept;

    void add(Key k, Value v);
    Value drop(Key k);
    Value &get(Key k);
    const Value &get(Key k) const;

    bool has(Key k) const noexcept;
    void rehash(size_t newCapacity);
    void clear() noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;
    void swap(CuckooTable &other) noexcept;

    double loadFactor() const noexcept;
    void setMaxLoadFactor(double maxLf) noexcept;
    void setMaxKickCount(size_t maxKicks) noexcept;

  private:
    Vector< entryType > table1_;
    Vector< entryType > table2_;
    size_t capacity_;
    size_t size_;
    Hash1 hasher1_;
    Hash2 hasher2_;
    Equal comparator_;
    double maxLoadFactor_;
    size_t maxKickCount_;
  };
}

#endif
