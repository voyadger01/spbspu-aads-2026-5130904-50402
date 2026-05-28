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

template< class Key, class Value, class Hash1, class Hash2, class Equal >
karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal >::CuckooTable(size_t capacity):
  table1_(capacity),
  table2_(capacity),
  capacity_(capacity),
  size_(0),
  hasher1_(),
  hasher2_(),
  comparator_(),
  maxLoadFactor_(0.5),
  maxKickCount_(capacity)
{}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal >::CuckooTable(const CuckooTable &other):
  table1_(other.table1_),
  table2_(other.table2_),
  capacity_(other.capacity_),
  size_(other.size_),
  hasher1_(other.hasher1_),
  hasher2_(other.hasher2_),
  comparator_(other.comparator_),
  maxLoadFactor_(other.maxLoadFactor_),
  maxKickCount_(other.maxKickCount_)
{}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal >::CuckooTable(CuckooTable &&other) noexcept:
  table1_(std::move(other.table1_)),
  table2_(std::move(other.table2_)),
  capacity_(other.capacity_),
  size_(other.size_),
  hasher1_(std::move(other.hasher1_)),
  hasher2_(std::move(other.hasher2_)),
  comparator_(std::move(other.comparator_)),
  maxLoadFactor_(other.maxLoadFactor_),
  maxKickCount_(other.maxKickCount_)
{
  other.capacity_ = 0;
  other.size_ = 0;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal > &
karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal >::operator=(const CuckooTable &other)
{
  if (this != std::addressof(other)) {
    table1_ = other.table1_;
    table2_ = other.table2_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    hasher1_ = other.hasher1_;
    hasher2_ = other.hasher2_;
    comparator_ = other.comparator_;
    maxLoadFactor_ = other.maxLoadFactor_;
    maxKickCount_ = other.maxKickCount_;
  }
  return *this;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal > &
karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal >::operator=(CuckooTable &&other) noexcept
{
  if (this != std::addressof(other)) {
    table1_ = std::move(other.table1_);
    table2_ = std::move(other.table2_);
    capacity_ = other.capacity_;
    size_ = other.size_;
    hasher1_ = std::move(other.hasher1_);
    hasher2_ = std::move(other.hasher2_);
    comparator_ = std::move(other.comparator_);
    maxLoadFactor_ = other.maxLoadFactor_;
    maxKickCount_ = other.maxKickCount_;

    other.capacity_ = 0;
    other.size_ = 0;
  }
  return *this;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
bool karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal >::empty() const noexcept
{
  return size_ == 0;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
size_t karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal >::size() const noexcept
{
  return size_;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
double karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal >::loadFactor() const noexcept
{
  return static_cast< double >(size_) / (capacity_ * 2);
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
void karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal >::setMaxLoadFactor(double maxLf) noexcept
{
  maxLoadFactor_ = maxLf;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
void karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal >::setMaxKickCount(size_t maxKicks) noexcept
{
  maxKickCount_ = maxKicks;
}

template< class Key, class Value, class Hash1, class Hash2, class Equal >
void karpovich::CuckooTable< Key, Value, Hash1, Hash2, Equal >::clear() noexcept
{
  table1_ = Vector< entryType >(capacity_);
  table2_ = Vector< entryType >(capacity_);
  size_ = 0;
}

#endif
