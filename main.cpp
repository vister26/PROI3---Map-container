#include "rbtree.h"


// ==================================
// test program
// ==================================
int main(int argc,char *argv[]) {
    int nodelist[] = {8,5,4,7,10,9,17,3,6};
    string datalist[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    NodeVisitor<int, string> *v;

    // insert all the data into the tree
    RedBlackTree<int, string> *root = new RedBlackTree<int, string>(1,"z");

    // need to do an ugly calculation to figure out length of the nodelist array
    // if i used a collection object instead of an array, then I couldn't have
    // done static initialization. so its a tradeoff
    for(int i=0;i<(sizeof(nodelist)/sizeof(nodelist[0]));i++) {
        root->insert(nodelist[i], datalist[i]);
    }

    // anonymous class implementing the NodeVisitor interface
    v = new IntNodeVisitor;

    // print the header
    //cout << "    = ";
    // visit all the nodes in order
    //root->inorder(v,0);
    //root->m_left->m_right->m_val
    //root->m_right->m_left
    //root->m_right->m_right->m_left->m_val
    cout << endl;
    root->BFS(v,0);
    // print a newline
    cout << endl;



    // find the specified element and print its value
    const RedBlackTree<int, string> *x = root->find(10);
    cout << x->str() << endl;

    // no garbage collection, need to explicitly delete
    delete root; // will recursively delete all the nodes
    delete v;
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
