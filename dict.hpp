#ifndef DICT_HPP_
#define DICT_HPP_

#include "dict.h"

template<typename Key, typename T, typename Compare, typename Allocator>
Dict<Key, T, Compare, Allocator>::Dict( const Compare& comp, const Allocator& alloc )
{

}

template<typename Key, typename T, typename Compare, typename Allocator>
Dict<Key, T, Compare, Allocator>::Dict(const Allocator& alloc)
{

}

#endif // DICT_HPP_

