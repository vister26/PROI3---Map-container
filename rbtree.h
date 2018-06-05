#ifndef RBTREE_H_
#define RBTREE_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// requires forward declaration to resolve cycle between NodeVisitor and RBTree
template<typename T, typename D> class RBTree;
// use an abstract class for the node visitor. it is templatized to match the templated RBTree declaration
template<typename T, typename D> class NodeVisitor {
public:
    // need a virtual destructor for the concrete classes
    virtual ~NodeVisitor() {}

    // ise a pure virtual function so a concrete class must implement
    // the proper signature
    virtual void visit(const RBTree<T,D> *node) = 0;
};

// in line with the STL conventions, this template uses 'by-value' semantics for the contained
// object. This means that the 'T' object will need to have the correct constructor and copy assignment
// semantics or it won't work. primitive types are OK but object instances would have to be
// put together correctly.
template<typename T, typename D> class RBTree {

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

    // use a common instance variable naming convention 'm_'. others use a single leading '_'
    int m_color;
    T m_val;
    D m_dat;
    RBTree *m_left;
    RBTree *m_right;

    RBTree(RBTree *b);

    void copy(RBTree *x);

    RBTree* RBinsertLeft(T k, D d, int sw);
    RBTree* RBinsertRight(T k, D d,int sw) ;
    RBTree* rotLeft();
    RBTree* rotRight();

    RBTree *RBinsert(T k, D d,int sw);

// ==================================================
// PUBLIC METHODS
// ==================================================
public:
    // construct with an initial value
    RBTree(T x, D d);

    ~RBTree();

    // return a string representation
    string str() const;

    // 'const' means this method doesn't change the object state
    T val() const {
        return m_val;
    }

    // 'const' means this method doesn't change the object state
    int color() const {
        return m_color;
    }

    // 'const' means this method doesn't change the object state
    D dat() const {
        return m_dat;
    }

    // 'const' means this method doesn't change the object state
    // and it returns a pointer to a const node that the caller
    // cannot change, only inspect
    const RBTree *find(const T &key) const;

    // 'const' means this method doesn't change the object state
    // and the visitor is not allowed to change the object state.
    // that may not be what is desired but is used here to
    // illustrate something you can do in C++ that you can't do
    // in the other languages and that illustrates the bias towards
    // extensive static type checking
    void inorder(NodeVisitor<T,D> *visitor,int depth) const;

    // Preszukiwanie wszerz
    void BFS(NodeVisitor<T,D> *visitor,int depth) const;

    RBTree *insert(T k, D d) {
        RBTree *b;
        b = RBinsert(k, d, 0);
        m_color = black;
        return b;
    }
};

// define a concrete class for the node visitor
class IntNodeVisitor : public NodeVisitor<int,string> {
public:
    virtual ~IntNodeVisitor() {}

    // the node is 'const' so the visitor can't change it, only look at it
    virtual void visit(const RBTree<int, string> *node) {
        if (node->val() != 0) {
            cout << "(" << node->val() << ":" << node->color() << ":" << node->dat() << "), ";
        }
    }
};

#include "rbtree.hpp"

#endif // RBTREE_H_
