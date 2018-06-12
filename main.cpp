#include "rbtree.h"
#include "dict.h"

// ==================================
// test program
// ==================================
int main(int argc,char *argv[]) {

/*
    int datalist[] = {8,5,4,7,10,9,17,3,6};
    string nodelist[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};

    // insert all the data into the tree
    RBTree<string, int> *root = new RBTree<string, int>("z", 1);
    // need to do an ugly calculation to figure out length of the nodelist array
    // if i used a collection object instead of an array, then I couldn't have
    // done static initialization. so its a tradeoff
    for(int i=0;i<(sizeof(nodelist)/sizeof(nodelist[0]));i++) {
        root->insert(nodelist[i], datalist[i]);
    }

    cout << endl;
    root->BFS();
    //root->begin();
    // print a newline
    cout << endl;

    // find the specified element and print its value
    const RBTree<string, int> *x = root->find("a");
    cout << x->str() << endl;

    // no garbage collection, need to explicitly delete
    delete root; // will recursively delete all the nodes

*/
    vector<int> datalist = {8,5,4,7,10,9,17,3,6,22};
    vector<std::string> keylist = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};

    Dict<std::string, int> *dict = new Dict<std::string, int>("z", 1);
    Dict<std::string, int>::const_iterator iter;

    dict->insert(keylist, datalist);
    dict->displayDict();

    for(iter = dict->begin(); iter <= dict->end(); iter = dict->next())
        cout << dict->first() << '\t';

    dict->erase(dict->find("g"));
    dict->erase(dict->find("c"));
    dict->erase(dict->find("h"));
    dict->erase(dict->find("j"));
    dict->erase(dict->find("e"));
    dict->erase(dict->find("a"));
    dict->erase(dict->find("b"));

    cout << endl << endl;
    dict->displayDict();
    dict->clear();
    dict = new Dict<std::string, int>("z", 1);
    cout << endl << endl;
    dict->insert("b", 1);
    dict->insert("b", 2);
    dict->displayDict();

}


// ===================================================================
// UPDATE 2006-01-29
// there are memory leaks that need to be fixed.
// 1. the algorithm leaks nodes after a rotate
//  two possible fixes :
//  find where the leaks occur and do the needed deletes
//      in this case the 'copy' method handles
//              deleting unused nodes
//      use an appropriate smart pointer to handle deleteing
// 2. the tree is not properly disposed of when the program completes
//     In the STL tradition a delete of the tree should
//     delete all tree resources but not the contained data. the application
//     should handle deleting the contained data elements, if needed, prior
//     to deleting the tree. In this case a recursive delete of the
//     nodes works gets rid of the tree resources
//
// these issue show that one of the big difficulties in C++ is to
// handle disposing of data after you are done with it. that is indeed a
// source of many C++ program errors of the type that are related more to
// dealing with the complexity of the language rather than the solving
// the problem. In this code the leaks are probably fixed but there is always
// a lingering doubt "Did I get all the leaks?"
// Thats a problem with C++, its hard to be certain.
//
// a modern approach is to use smart pointers to simulate garbage
// collection. the Boost library referenced counted smart pointers
// will be included in the next standard revision of the C++ library
// so they are used here to handle all the cases.
// ===================================================================
