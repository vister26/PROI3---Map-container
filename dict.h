#ifndef DICT_H_
#define DICT_H_

#include <memory>
#include <functional>
#include <utility>
#include "rbtree.h"
#include <map>

template<
    typename Key,
    typename Dat,
    typename Compare,
    typename Allocator
> class Dict;

template<
    typename Key,
    typename T,
    typename Compare = std::less<Key>,
    typename Allocator = std::allocator<std::pair<const Key, T> >
> class Dict
{
private:

public:
    explicit Dict(const Compare& comp = Compare(), const Allocator& alloc = Allocator());
    explicit Dict(const Allocator& alloc);
};

#include "dict.hpp"

#endif // DICT_H_
