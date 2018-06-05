#ifndef RBTREE_H_
#define RBTREE_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// SEE UPDATE COMMENTS AT END OF FILE
// 2006-01.29 fixed memory leaks
// eliminate need to qualify standard library with std::
using namespace std;
// ===============================================================
// C++ NEEDS SOME DECLARATIONS BEFORE THE MAIN RedBlackTree class.
// skip down a little to line this up with the other side
// ===============================================================
// requires forward declaration to resolve cycle between NodeVisitor and RedBlackTree
template<typename T, typename D> class RedBlackTree;
// use an abstract class for the node visitor. it is templatized to match the templated RedBlackTree declaration
template<typename T, typename D> class NodeVisitor {
public:
    // need a virtual destructor for the concrete classes
    virtual ~NodeVisitor() {}

    // ise a pure virtual function so a concrete class must implement
    // the proper signature
    virtual void visit(const RedBlackTree<T,D> *node) = 0;
};

// =============================================
// >>>>>>>>>>>>>>>>> RED BLACK TREE STARTS HERE
// =============================================
// in line with the STL conventions, this template uses 'by-value' semantics for the contained
// object. This means that the 'T' object will need to have the correct constructor and copy assignment
// semantics or it won't work. primitive types are OK but object instances would have to be
// put together correctly.
template<typename T, typename D> class RedBlackTree {

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
    RedBlackTree *m_left;
    RedBlackTree *m_right;

    RedBlackTree(RedBlackTree *b);

    void copy(RedBlackTree *x);

    RedBlackTree* RBinsertLeft(T k, D d, int sw);
    RedBlackTree* RBinsertRight(T k, D d,int sw) ;
    RedBlackTree* rotLeft();
    RedBlackTree* rotRight();

    RedBlackTree *RBinsert(T k, D d,int sw) {
        RedBlackTree *b = 0;
        RedBlackTree *x;
        RedBlackTree *l;
        RedBlackTree *ll;
        RedBlackTree *r;
        RedBlackTree *rr;

        // if current node is a 4 node, split it by flipping its colors
        // if both children of this node are red, change this one to red
        // and the children to black
        l = m_left;
        r = m_right;
        if ((l != 0)&&(l->m_color==red)&&(r != 0)&&(r->m_color==red)) {
            m_color = red;
            l->m_color = black;
            r->m_color = black;
        }

        // go left or right depending on key relationship
        if (k < m_val) {
            // recursively insert
            b = RBinsertLeft(k, d, 0);

            // on the way back up check if a rotation is needed
            // if search path has two red links with same orientation
            // do a single rotation and flip the color bits
            l = m_left;
            if ((m_color == red)&&(l != 0)&&(l->m_color == red)&&(sw == 1)) {
                x = rotRight();
                if (x != 0) {
                    // copy returned node to 'this'
                    copy(x);
                }
            }

            // flip the color bits
            l = m_left;
            if (l != 0) {
                ll = l->m_left;
                if (ll != 0) {
                    if ((l->m_color == red)&&(ll->m_color == red)) {
                        x = rotRight();
                        if (x != 0) {
                            copy(x);
                        }
                        m_color = black;
                        r = m_right;
                        if (r != 0) {
                           r->m_color = red;
                        }
                    }
                }
            }
        }
        else {
            b = RBinsertRight(k, d, 1);

            // on the way back up check if a rotation is needed
            // if search path has two red links with same orientation
            // do a single rotation and flip the color bits
            r = m_right;
            if ((m_color == red)&&(r != 0)&&(r->m_color == red)&&(sw == 0)) {
                x = rotLeft();
                if (x != 0) {
                    // copy returned node to 'this'
                    copy(x);
                }
            }

            // flip the color bits
            r = m_right;
            if (r != 0) {
                rr = r->m_right;
                if (rr != 0) {
                    if ((r->m_color == red)&&(rr->m_color == red)) {
                        x = rotLeft();
                        if (x != 0) {
                           // copy returned node to 'this'
                            copy(x);
                        }
                        m_color = black;
                        l = m_left;
                        if (l != 0) {
                           l->m_color = red;
                        }
                    }
                }
            }
        }

        return b;
    }

// ==================================================
// PUBLIC METHODS
// ==================================================
public:
    // construct with an initial value
    RedBlackTree(T x, D d) {
        m_val      = x;
        m_dat      = d;
        m_left     = 0;
        m_right    = 0;
        m_color    = red;
    }

    ~RedBlackTree() {

        if (m_left != 0) {
            delete m_left;
        }
        if (m_right != 0) {
            delete m_right;
        }
    }

    // return a string representation
    string str() const {
        stringstream s(stringstream::out);
        // m_val (type T) must have the proper ostream insertion operator
        // or this implementation won't work
        s << "[" << m_val << "," << m_color << "]";
        return s.str();
    }

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
    const RedBlackTree *find(const T &key) const {
        const RedBlackTree *result = 0;
        if (key == m_val) {
            result = this;
        }
        else if (key < m_val) {
            if (m_left != 0) {
                result = m_left->find(key);
            }
        }
        else {
            if (m_right != 0) {
                result = m_right->find(key);
            }
        }
        return result;
    }

    // 'const' means this method doesn't change the object state
    // and the visitor is not allowed to change the object state.
    // that may not be what is desired but is used here to
    // illustrate something you can do in C++ that you can't do
    // in the other languages and that illustrates the bias towards
    // extensive static type checking
    void inorder(NodeVisitor<T,D> *visitor,int depth) const {
        if (m_left != 0) {
            m_left->inorder(visitor,depth+1);
        }
        visitor->visit(this,depth);
        if (m_right != 0) {
            m_right->inorder(visitor,depth+1);
        }
    }

    // Preszukiwanie wszerz
    void BFS(NodeVisitor<T,D> *visitor,int depth) const {
            vector<const RedBlackTree*> kolejka;
            const RedBlackTree *v;  // wskaznik na aktualny element ktoey wypisujemy
            v = this;


            kolejka.push_back(v);                           // dodajemy pierwszy element do kolejki
            while( !kolejka.empty() )                       // dpoki kolejka sie nie oprozni
            {

                v = kolejka.front();                        // pobieramy element z poczatku
                visitor->visit(v);                        // wyswietlamy go

                cout << "kolejka: ";
                for(int i = 0; i < kolejka.size(); ++i)
                    cout << kolejka[i]->m_val<<' ';
                cout << endl;

                if( v->m_left != 0)                         // wpisujemy do kolejki prawe i lewe podrzewo, jesli takowe istnieja
                    kolejka.push_back(v->m_left);

                if( v->m_right != 0 )
                    kolejka.push_back(v->m_right);

                kolejka.erase(kolejka.begin());             // usuwamy z kolejki pierwszy, wypisany wczesniej element

            }


    }
////

    RedBlackTree *insert(T k, D d) {
        RedBlackTree *b;
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
    virtual void visit(const RedBlackTree<int, string> *node) {
        if (node->val() != 0) {
            cout << "(" << node->val() << ":" << node->color() << ":" << node->dat() << "), ";
        }
    }
};

#include "rbtree.hpp"

#endif // RBTREE_H_
