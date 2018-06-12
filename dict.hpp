#ifndef DICT_HPP_
#define DICT_HPP_

#include "dict.h"


template<typename Key, typename Dat>
Dict<Key, Dat>::Dict()
{
    root = NULL;
}

template<typename Key, typename Dat>
Dict<Key, Dat>::Dict(const Dict& x)
{

}

template<typename Key, typename Dat>
Dict<Key, Dat>::Dict(const Key& k, const Dat& d)
{
    root = new Tree(k, d);
}

template<typename Key, typename Dat>
typename Dict<Key, Dat>::const_iterator Dict<Key, Dat>::find(const Key& k)
{
    return root->find(k);
}

template<typename Key, typename Dat>
std::pair<typename RBTree<Key, Dat>::iterator, bool> Dict<Key, Dat>::insert(const std::vector<Key> keylist, const std::vector<Dat> datalist)
{
    iterator inserted = NULL;
    bool isGood = true;
    bool loop = false;
    for(unsigned i = 0; i < keylist.size(); ++i) {

        iteratorlist.clear();
        iteratorlist = root->createList();
        for(int j = 0; j < iteratorlist.size(); ++j){
            //cout << iteratorlist[j]->val() << "==" << keylist[i] << endl;
            if( iteratorlist[j]->val() == keylist[i] ){
                isGood = false;
                loop = true;
                break;
            }
        }
        //cout << endl;
        if(loop){
            loop = false;
            continue;
        }
        inserted = root->insert(keylist[i], datalist[i]);
    }

    return std::make_pair(inserted, isGood);
}

template<typename Key, typename Dat>
std::pair<typename RBTree<Key, Dat>::iterator, bool> Dict<Key, Dat>::insert(const Key& k, const Dat& d)
{
    iterator inserted = NULL;
    bool isGood = true;
    iteratorlist.clear();
    iteratorlist = root->createList();
    for(int j = 0; j < iteratorlist.size(); ++j){
        if( iteratorlist[j]->val() == k ){
            isGood = false;
            return std::make_pair(nullptr, isGood);
        }
    }
        inserted = root->insert(k, d);
        return std::make_pair(inserted, isGood);
}

template<typename Key, typename Dat>
void Dict<Key, Dat>::erase(const_iterator pos)
{
    std::vector<const Tree*> nodelist;
    nodelist = root->createList();
    int i = 0;
    for(; nodelist[i] != pos; ++i);
    nodelist.erase(nodelist.begin()+i);

    std::vector<Key> keylist;
    std::vector<Dat> datalist;

    while(!nodelist.empty()){
        keylist.push_back(nodelist.front()->val());
        datalist.push_back(nodelist.front()->dat());
        nodelist.erase(nodelist.begin());
    }

    clear();
    root = new Tree(keylist.front(), datalist.front());
    keylist.erase(keylist.begin());
    datalist.erase(datalist.begin());
    insert(keylist, datalist);

}

template<typename Key, typename Dat>
void Dict<Key, Dat>::displayDict()
{
    root->BFS();
    return;
}

template<typename Key, typename Dat>
const Dat& Dict<Key, Dat>::at(const Key& k) const
{
    Tree *tree = root->find(k);
    return tree.dat();
}


template<typename Key, typename Dat>
void Dict<Key, Dat>::clear()
{
    delete root;
    root = NULL;
    return;
}


#endif // DICT_HPP_

