#ifndef RBTREE_HPP_
#define RBTREE_HPP_

template<typename Key, typename Dat>
RBTree<Key, Dat>::RBTree()
{
    t_val      = 0;
    t_dat      = 0;
    t_left     = 0;
    t_right    = 0;
    t_color    = red;
}

template<typename Key, typename Dat>
RBTree<Key, Dat>::RBTree(const Key& k, const Dat& d)
{
    t_val      = k;
    t_dat      = d;
    t_left     = 0;
    t_right    = 0;
    t_color    = red;
}

template<typename Key, typename Dat>
RBTree<Key, Dat>::RBTree( RBTree *b)
{
    t_val      = b->t_val;
    t_dat      = b->t_dat;
    t_left     = b->t_left;
    t_right    = b->t_right;
    t_color    = red;
}


template<typename Key, typename Dat>
RBTree<Key, Dat>::~RBTree()
{
    if (t_left != 0) {
        delete t_left;
    }
    if (t_right != 0) {
        delete t_right;
    }
}


template<typename Key, typename Dat>
void RBTree<Key, Dat>::copy(RBTree *x)
{
    t_val     = x->t_val;
    t_dat     = x->t_dat;
    t_left    = x->t_left;
    t_right   = x->t_right;
    t_color   = x->t_color;

    // node pointed to by 'x' is no longer needed, delete it.
    // first make sure the delete won't descend into other nodes
    x->t_left  = 0;
    x->t_right = 0;
    delete x;
}

template<typename Key, typename Dat>
RBTree<Key, Dat>* RBTree<Key, Dat>::RBinsertLeft(Key k, Dat d, int sw)
{
    RBTree *l;
    RBTree *b;

    l = t_left;
    if (l == 0) {
        t_left = b = new RBTree(k, d);
    }
    else {
        b = l->RBinsert(k, d, sw);
    }
    return b;
}

template<typename Key, typename Dat>
RBTree<Key, Dat>* RBTree<Key, Dat>::RBinsertRight(Key k, Dat d, int sw)
{
    RBTree *r;
    RBTree *b;

    r = t_right;
    if (r == 0) {
        t_right = b = new RBTree(k,d);
    }
    else {
        b = r->RBinsert(k, d, sw);
    }
    return b;
}

template<typename Key, typename Dat>
RBTree<Key, Dat>* RBTree<Key, Dat>::rotLeft()
{
    RBTree *x;
    RBTree *me;

    if (t_right == 0) return 0;
    // make the changes in a copy of current node __self
    // on return, the caller will copy in 'me' to current node
    me          = new RBTree(this);
    x           = me->t_right;
    me->t_right = x->t_left;
    x->t_left   = me;
    return   x;
}

template<typename Key, typename Dat>
RBTree<Key, Dat>* RBTree<Key, Dat>::rotRight()
{
    RBTree *x;
    RBTree *me;

    if (t_left == 0) return 0;

    // make the changes in a copy of current node __self
    // on return, the caller will copy in 'me' to current node
    me          = new RBTree(this);
    x           = me->t_left;
    me->t_left  = x->t_right;
    x->t_right  = me;
    return x;
}

template<typename Key, typename Dat>
string RBTree<Key, Dat>::str() const
{
    stringstream s(stringstream::out);
    // t_val (type Key) must have the proper ostream insertion operator
    // or this implementation won't work
    s << "[" << t_val << "," << t_color << "]";
    return s.str();
}

template<typename Key, typename Dat>
const RBTree<Key, Dat>* RBTree<Key, Dat>::find(const Key &key) const {
    const RBTree *result = 0;
    if (key == t_val) {
        result = this;
    }
    else if (key < t_val) {
        if (t_left != 0) {
            result = t_left->find(key);
        }
    }
    else {
        if (t_right != 0) {
            result = t_right->find(key);
        }
    }
    return result;
}
/*
template<typename Key, typename Dat>
void RBTree<Key, Dat>::inorder(NodeVisitor<Key, Dat> *visitor,int depth) const
{
    if (t_left != 0) {
        t_left->inorder(visitor,depth+1);
    }
    visitor->visit(this,depth);
    if (t_right != 0) {
        t_right->inorder(visitor,depth+1);
    }
}
*/
template<typename Key, typename Dat>
void RBTree<Key, Dat>::BFS() const
{

        vector<const RBTree*> lista;

        lista = this->createList();
        while(!lista.empty()){
            cout << lista.front()->t_val << colorName[lista.front()->t_color] << ": " << lista.front()->t_dat;   // wyswietlamy go
            cout << "\tkolejka: ";
            for(unsigned i = 0; i < lista.size(); ++i)
                cout << lista[i]->t_val<<' ';
            cout << endl;

            lista.erase(lista.begin());
        }
}

template<typename Key, typename Dat>
std::vector<const RBTree<Key, Dat>*> RBTree<Key, Dat>::createList() const
{
    vector<const RBTree*> kolejka;
    vector<const RBTree*> lista;
    const RBTree *v;  // wskaznik na aktualny element ktoey wypisujemy
    v = this;

    kolejka.push_back(v);                           // dodajemy pierwszy element do kolejki
    while( !kolejka.empty() )                       // dpoki kolejka sie nie oprozni
    {
        v = kolejka.front();                        // dodajemy do listy element z poczatku
        lista.push_back(v);

        if( v->t_left != 0)                         // wpisujemy do kolejki prawe i lewe podrzewo, jesli takowe istnieja
            kolejka.push_back(v->t_left);

        if( v->t_right != 0 )
            kolejka.push_back(v->t_right);

        kolejka.erase(kolejka.begin());             // usuwamy z kolejki pierwszy, wypisany wczesniej element
    }
    return lista;
}

template<typename Key, typename Dat>
RBTree<Key, Dat>* RBTree<Key, Dat>::insert(Key k, Dat d) {
        RBTree *b;
        b = RBinsert(k, d, 0);
        t_color = black;
        return b;
    }

template<typename Key, typename Dat>
RBTree<Key, Dat>* RBTree<Key, Dat>::RBinsert(Key k, Dat d,int sw)
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
    l = t_left;
    r = t_right;
    if ((l != 0)&&(l->t_color==red)&&(r != 0)&&(r->t_color==red)) {
        t_color = red;
        l->t_color = black;
        r->t_color = black;
    }

    // go left or right depending on key relationship
    if (k < t_val) {
        // recursively insert
       b = RBinsertLeft(k, d, 0);

        // on the way back up check if a rotation is needed
        // if search path has two red links with same orientation
        // do a single rotation and flip the color bits
        l = t_left;
        if ((t_color == red)&&(l != 0)&&(l->t_color == red)&&(sw == 1)) {
            x = rotRight();
            if (x != 0) {
                // copy returned node to 'this'
                copy(x);
            }
        }

        // flip the color bits
        l = t_left;
        if (l != 0) {
            ll = l->t_left;
            if (ll != 0) {
                if ((l->t_color == red)&&(ll->t_color == red)) {
                    x = rotRight();
                    if (x != 0) {
                        copy(x);
                    }
                    t_color = black;
                    r = t_right;
                    if (r != 0) {
                       r->t_color = red;
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
        r = t_right;
        if ((t_color == red)&&(r != 0)&&(r->t_color == red)&&(sw == 0)) {
            x = rotLeft();
            if (x != 0) {
                // copy returned node to 'this'
                copy(x);
            }
        }

        // flip the color bits
        r = t_right;
        if (r != 0) {
            rr = r->t_right;
            if (rr != 0) {
               if ((r->t_color == red)&&(rr->t_color == red)) {
                   x = rotLeft();
                   if (x != 0) {
                       // copy returned node to 'this'
                        copy(x);
                    }
                    t_color = black;
                    l = t_left;
                    if (l != 0) {
                       l->t_color = red;
                    }
                }
            }
        }
    }

    return b;
}

#endif // RBTREE_HPP_
