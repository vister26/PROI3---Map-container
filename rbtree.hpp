#ifndef RBTREE_HPP_
#define RBTREE_HPP_

template<typename T, typename D>
RedBlackTree<T, D>::RedBlackTree( RedBlackTree *b)
{
    m_val      = b->m_val;
    m_dat      = b->m_dat;
    m_left     = b->m_left;
    m_right    = b->m_right;
    m_color    = red;
}

template<typename T, typename D>
void RedBlackTree<T, D>::copy(RedBlackTree *x)
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
RedBlackTree<T, D>* RedBlackTree<T, D>::RBinsertLeft(T k, D d, int sw)
{
    RedBlackTree *l;
    RedBlackTree *b;

    l = m_left;
    if (l == 0) {
        m_left = b = new RedBlackTree(k, d);
    }
    else {
        b = l->RBinsert(k, d, sw);
    }
    return b;
}

template<typename T, typename D>
RedBlackTree<T, D>* RedBlackTree<T, D>::RBinsertRight(T k, D d, int sw)
{
    RedBlackTree *r;
    RedBlackTree *b;

    r = m_right;
    if (r == 0) {
        m_right = b = new RedBlackTree(k,d);
    }
    else {
        b = r->RBinsert(k, d, sw);
    }
    return b;
}

template<typename T, typename D>
RedBlackTree<T, D>* RedBlackTree<T, D>::rotLeft()
{
    RedBlackTree *x;
    RedBlackTree *me;

    if (m_right == 0) return 0;
    // make the changes in a copy of current node __self
    // on return, the caller will copy in 'me' to current node
    me          = new RedBlackTree(this);
    x           = me->m_right;
    me->m_right = x->m_left;
    x->m_left   = me;
    return   x;
}

template<typename T, typename D>
RedBlackTree<T, D>* RedBlackTree<T, D>::rotRight()
{
    RedBlackTree *x;
    RedBlackTree *me;

    if (m_left == 0) return 0;

    // make the changes in a copy of current node __self
    // on return, the caller will copy in 'me' to current node
    me          = new RedBlackTree(this);
    x           = me->m_left;
    me->m_left  = x->m_right;
    x->m_right  = me;
    return x;
}

#endif // RBTREE_HPP_
