#ifndef RBTREE_H_
#define RBTREE_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// requires forward declaration to resolve cycle between NodeVisitor and RBTree
template<typename Key, typename Dat> class RBTree;

//template <typename Key, typename Dat> RBTree* Global<Key, Dat>::pVar = new RBTree;
//template<typename Key, typename Dat>
//RBTree<Key, Dat> *t_root = NULL;

// globalny wskaznik na korzen drzewa

// in line with the STL conventions, this template uses 'by-value' semantics for the contained
// object. This means that the 'T' object will need to have the correct constructor and copy assignment
// semantics or it won't work. primitive types are OK but object instances would have to be
// put together correctly.
template<typename Key, typename Dat> class RBTree {

private:
    /*
    Red/Black tree implementation based on
    Algorithms in C++, Sedgewick
    Introduction To Algorithms Cormen, Thomas H. / Leiserson, Charl es E . / Rivest, Ronald L . The MIT Press 07/1990
    NOTE : LOOK AT END OF FILE TO SEE DIFFERENCES IN TRAVERSAL IDIOMS
    */

    // yes, i could use an enum but since i want to print the values, using an enum is more
    // trouble than it is worth.
    static const int red   = 0;
    static const int black = 1;
    const char colorName[2] = {'R', 'B'};

    // use a common instance variable naming convention 't_'. others use a single leading '_'
    int t_color;
    Key t_val;
    Dat t_dat;
    //RBTree *t_root;
    RBTree *t_left;
    RBTree *t_right;

    RBTree(RBTree *b);

    void copy(RBTree *x);

    RBTree* RBinsertLeft(Key k, Dat d, int sw);
    RBTree* RBinsertRight(Key k, Dat d,int sw);
    RBTree* rotLeft();
    RBTree* rotRight();

    RBTree *RBinsert(Key k, Dat d,int sw);

// ==================================================
// PUBLIC METHODS
// ==================================================
public:
    // construct with an initial value
    RBTree();
    RBTree(const Key& k, const Dat& d);

    ~RBTree();

    typedef RBTree* iterator;
    typedef const RBTree* const_iterator;
    //iterator begin() { return t_root; }

    // return a string representation
    string str() const;

    // 'const' means this method doesn't change the object state
    Key val() const {
        return t_val;
    }

    // 'const' means this method doesn't change the object state
    int color() const {
        return t_color;
    }

    // 'const' means this method doesn't change the object state
    Dat dat() const {
        return t_dat;
    }

    // 'const' means this method doesn't change the object state
    // and it returns a pointer to a const node that the caller
    // cannot change, only inspect
    const RBTree *find(const Key &key) const;

    std::vector<const RBTree*> createList() const;

    // 'const' means this method doesn't change the object state
    // and the visitor is not allowed to change the object state.
    // that may not be what is desired but is used here to
    // illustrate something you can do in C++ that you can't do
    // in the other languages and that illustrates the bias towards
    // extensive static type checking
    //void inorder(NodeVisitor<Key, Dat> *visitor,int depth) const;

    // Preszukiwanie wszerz
    void BFS() const;

    RBTree *insert(Key k, Dat d);
};

#include "rbtree.hpp"

#endif // RBTREE_H_
