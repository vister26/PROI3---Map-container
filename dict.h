#ifndef DICT_H_
#define DICT_H_

#include "rbtree.h"

template<
    typename Key,
    typename Dat
> class Dict;

template<
    typename Key,
    typename Dat
> class Dict
{
private:
    typedef  RBTree<Key, Dat> Tree;
    Tree *root = NULL;
    std::vector<const Tree*> iteratorlist;
    unsigned iteratorCurPos;

public:
    typedef typename Tree::iterator iterator;
    typedef typename Tree::const_iterator const_iterator;

    const_iterator begin() {
        iteratorlist.clear();
        iteratorlist = root->createList();
        iteratorCurPos = 0;
        //cout << "valbeg: " <<iteratorlist[0]->val() << endl;
        return iteratorlist.front();
    }
    const_iterator end(){
        //cout << "valend: " <<iteratorlist.back()->val() << endl;
        return iteratorlist.back();
    }
    const_iterator next(){
        ++iteratorCurPos;
        return iteratorlist[iteratorCurPos];
    }
    const_iterator prev(){
        --iteratorCurPos;
        return iteratorlist[iteratorCurPos];
    }

    Key first() const{
        return iteratorlist[iteratorCurPos]->val();
    }

    Dat second() const{
        return iteratorlist[iteratorCurPos]->dat();
    }

    explicit Dict();
    Dict(const Key& k, const Dat& d );
    Dict(const Dict& x);

    std::pair<iterator, bool> insert(const std::vector<Key> keylist, const std::vector<Dat> datalist);
    std::pair<iterator, bool> insert(const Key& k, const Dat& d);
    const_iterator find(const Key& k);
    void erase(const_iterator pos);
    void displayDict();
    const Dat& at(const Key& k) const;
    void clear();
};

#include "dict.hpp"

#endif // DICT_H_
