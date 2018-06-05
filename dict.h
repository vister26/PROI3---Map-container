#ifndef DICT_H_
#define DICT_H_

#include <memory>
#include <functional>
#include <utility>
#include "rbtree.h"

template<
    typename Key,
    typename T,
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
public:

    explicit Dict( const Compare& comp = Compare(), const Allocator& alloc = Allocator() );
};

#include "dict.hpp"

#endif // DICT_H_
