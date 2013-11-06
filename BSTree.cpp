/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 5 - Trees
    28 October 2013

*****************************************************/

#include "BSTree.h"

BSTree::BSTree ( void ) {}

BSTree::~BSTree () {}

bool BSTree::isEmpty() const {}

Record BSTree::Find (const KeyType& key) const {}

void BSTree::Insert (const Record&) {}

void BSTree::InOrderTraversal ( void (*) (const Record&)) {}

void BSTree::PreOrderTraversal ( void (*) (const Record&)) {}

void BSTree::PostOrderTraversal ( void (*) (const Record&)) {}

unsigned BSTree::Depth ( void ) const {}

void BSTree::Delete (const KeyType& key) {}
