#ifndef RBTREE_HPP_
#define RBTREE_HPP_

template<typename T, typename D>
RBTree<T, D>::RBTree( RBTree *b)
{
    m_val      = b->m_val;
    m_dat      = b->m_dat;
    m_left     = b->m_left;
    m_right    = b->m_right;
    m_color    = red;
}

template<typename T, typename D>
void RBTree<T, D>::copy(RBTree *x)
{
    m_val     = x->m_val;
    m_dat     = x->m_dat;
    m_left    = x->m_left;
    m_right   = x->m_right;
    m_color   = x->m_color;

    // UPDATE 2006-01-28
    // node pointed to by 'x' is no longer needed, delete it.
    // first make sure the delete won't descend into other nodes
    x->m_left  = 0;
    x->m_right = 0;
    delete x;
}

template<typename T, typename D>
RBTree<T, D>* RBTree<T, D>::RBinsertLeft(T k, D d, int sw)
{
    RBTree *l;
    RBTree *b;

    l = m_left;
    if (l == 0) {
        m_left = b = new RBTree(k, d);
    }
    else {
        b = l->RBinsert(k, d, sw);
    }
    return b;
}

template<typename T, typename D>
RBTree<T, D>* RBTree<T, D>::RBinsertRight(T k, D d, int sw)
{
    RBTree *r;
    RBTree *b;

    r = m_right;
    if (r == 0) {
        m_right = b = new RBTree(k,d);
    }
    else {
        b = r->RBinsert(k, d, sw);
    }
    return b;
}

template<typename T, typename D>
RBTree<T, D>* RBTree<T, D>::rotLeft()
{
    RBTree *x;
    RBTree *me;

    if (m_right == 0) return 0;
    // make the changes in a copy of current node __self
    // on return, the caller will copy in 'me' to current node
    me          = new RBTree(this);
    x           = me->m_right;
    me->m_right = x->m_left;
    x->m_left   = me;
    return   x;
}

template<typename T, typename D>
RBTree<T, D>* RBTree<T, D>::rotRight()
{
    RBTree *x;
    RBTree *me;

    if (m_left == 0) return 0;

    // make the changes in a copy of current node __self
    // on return, the caller will copy in 'me' to current node
    me          = new RBTree(this);
    x           = me->m_left;
    me->m_left  = x->m_right;
    x->m_right  = me;
    return x;
}

template<typename T, typename D>
RBTree<T, D>::RBTree(T x, D d)
{
    m_val      = x;
    m_dat      = d;
    m_left     = 0;
    m_right    = 0;
    m_color    = red;
}

template<typename T, typename D>
RBTree<T, D>::~RBTree()
{
    if (m_left != 0) {
        delete m_left;
    }
    if (m_right != 0) {
        delete m_right;
    }
}

template<typename T, typename D>
string RBTree<T, D>::str() const
{
    stringstream s(stringstream::out);
    // m_val (type T) must have the proper ostream insertion operator
    // or this implementation won't work
    s << "[" << m_val << "," << m_color << "]";
    return s.str();
}

template<typename T, typename D>
const RBTree<T, D>* RBTree<T, D>::find(const T &key) const {
    const RBTree *result = 0;
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

template<typename T, typename D>
void RBTree<T,D>::inorder(NodeVisitor<T,D> *visitor,int depth) const
{
    if (m_left != 0) {
        m_left->inorder(visitor,depth+1);
    }
    visitor->visit(this,depth);
    if (m_right != 0) {
        m_right->inorder(visitor,depth+1);
    }
}

template<typename T, typename D>
void RBTree<T,D>::BFS(NodeVisitor<T,D> *visitor,int depth) const
{
        vector<const RBTree*> kolejka;
        const RBTree *v;  // wskaznik na aktualny element ktoey wypisujemy
        v = this;

        kolejka.push_back(v);                           // dodajemy pierwszy element do kolejki
        while( !kolejka.empty() )                       // dpoki kolejka sie nie oprozni
        {
            v = kolejka.front();                        // pobieramy element z poczatku
            visitor->visit(v);                         // wyswietlamy go

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

template<typename T, typename D>
RBTree<T, D>* RBTree<T, D>::RBinsert(T k, D d,int sw)
{
    RBTree *b = 0;
    RBTree *x;
    RBTree *l;
    RBTree *ll;
    RBTree *r;
    RBTree *rr;

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

#endif // RBTREE_HPP_
