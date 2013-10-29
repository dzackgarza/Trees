/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 5 - Trees
    28 October 2013

*****************************************************/
#ifndef TREES_H
#define TREES_H
#define ItemTpye int

/** Class Invariants **/

class Tree {
    struct node
    {
        node* parent;
        node* left_child;
        node* right_child;
        ItemType data;
    };
    node* root;

    public:

    Tree( void );
    ~Tree();
    bool isEmpty();
    unsigned depth();
    ItemType getItem();
    void Delete (node*);
    void Add();
    void Print();

}
#endif
