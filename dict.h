#ifndef DICT_H_
#define DICT_H_

#include <memory>
#include <functional>
#include <utility>
#include <iterator>
#include "rbtree.h"

template<
    typename Key,
    typename Dat,
    typename Compare,
    typename Allocator
> class Dict;

template<
    typename Key,
    typename Dat,
    typename Compare = std::less<Key>,
    typename Allocator = std::allocator<std::pair<const Key, Dat> >
> class Dict
{
private:
    RBTree<Key, Dat> *root;

public:
    //typedef typename Dict<const Key, Dat>::iterator		Iterator;
    typedef typename std::pair<const Key, Dat>		value_type;

    explicit Dict(const Compare& comp = Compare(), const Allocator& alloc = Allocator());
    explicit Dict(const Allocator& alloc);
    Dict(const Dict& x);
    Dict(const Dict& x, const Allocator& alloc);

    std::pair<value_type*, bool> insert( const value_type& value );
};

#include "dict.hpp"

#endif // DICT_H_
