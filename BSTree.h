/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 5 - Trees
    28 October 2013

*****************************************************/
#ifndef TREES_H
#define TREES_H
#define Record int
#define KeyType int

/** Class Invariants
 *
 *  The BSTree remains a a BSTree throughout any and all operations.
 *  Left Child < Parent <= Right Child
 *
 **/
class BSTree {
    struct node
    {
        node* left_child;
        node* right_child;
        Record data;
    };
    node* root;

    public:

    // Pre:  None
    // Post: An empty BSTree is created.
    BSTree ( void );

    // Pre:  None
    // Post: The BSTress is destroyed and all allocated memory is released.
    ~BSTree ();

    // Pre: None
    // Post: RETVAL == True if Tree is empty
    bool isEmpty() const;

    // Pre:  !IsEmpty()
    // Post: RETVAL == Record item with this key. If the key is not in the tree,
    //       returns an "empty" Record.
    Record Find (const KeyType& key) const;

    // Pre:  None
    // Post: The Record is inserted into the BSTree in its proper place.
    //       If the tree already contains this key, does noting.
    //       Structure: Left Child < Parent <= Right Child
    void Insert (const Record&);

    // Pre:  !IsEmpty()
    // Post: BSTree is traversed in order and function is appled to each node.
    void InOrderTraversal ( void (*) (const Record&));

    // Pre:  !IsEmpty()
    // Post: BSTree is traversed pre-order and the function is appled to each node.
    void PreOrderTraversal ( void (*) (const Record&));

    // Pre:  !IsEmpty()
    // Post: BSTree is traversed post-order and function is applied to each node.
    void PostOrderTraversal ( void (*) (const Record&));

    // Pre: !IsEmpty()
    // Post: RETVAL == Depth of Tree, ie distance between root and furthest node.
    unsigned Depth ( void ) const;

    // Pre:  !IsEmpty()
    // Post: Record with this key is deleted and the tree is still a Binary Search Tree.
    //       If key is not in the tree, does nothing.
    void Delete (const KeyType& key);
};
#endif
