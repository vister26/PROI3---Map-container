#ifndef DICT_HPP_
#define DICT_HPP_

#include "dict.h"

template<typename Key, typename Dat, typename Compare, typename Allocator>
Dict<Key, Dat, Compare, Allocator>::Dict( const Compare& comp, const Allocator& alloc )
{
    root = NULL;
}

template<typename Key, typename Dat, typename Compare, typename Allocator>
Dict<Key, Dat, Compare, Allocator>::Dict(const Allocator& alloc)
{
    root = NULL;
}

template<typename Key, typename Dat, typename Compare, typename Allocator>
Dict<Key, Dat, Compare, Allocator>::Dict(const Dict& x)
{

}

template<typename Key, typename Dat, typename Compare, typename Allocator>
Dict<Key, Dat, Compare, Allocator>::Dict(const Dict& x, const Allocator& alloc)
{

}

template<typename Key, typename Dat, typename Compare, typename Allocator>
std::pair<std::pair<const Key, Dat>*, bool> Dict<Key, Dat, Compare, Allocator>::insert( const std::pair<const Key, Dat>& value )
{

}

#endif // DICT_HPP_

