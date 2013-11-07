/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 5 - Trees
    28 October 2013

*****************************************************/

#include "BSTree.h"
#include <iostream>
using namespace std;

bool BSTree::IsEmpty() const
{
    return (root==NULL);
}

BSTree::BSTree ( void )
{
    root = NULL;
}

// Public Delete
BSTree::~BSTree ()
{
    Delete_tree(root);
}

// Private Delete
// Traverses tree, recursively deleting left, then right, then parent leaves.
void BSTree::Delete_tree (node* current)
{
    if (current != NULL)
    {
        Delete_tree(current->left_child);
        Delete_tree(current->right_child);
        delete current;
    }
}

// Public Find
Record BSTree::Find (const KeyType& key) const
{
    return Find(key, root);
}

// Recursively traverse the tree until key is found, return NULL if not found.
Record BSTree::Find(const KeyType& key, node* current ) const
{
    if (current != NULL)
    {
        if (current->data == key)           // Found
            return current->data;
        else if (current->data < key)       // Continue left
            return Find(key, current->left_child);
        else    // current->data >= key     // Continue right
            return Find(key, current->right_child);
    }
    // Key not found, return an empty record.
    // #TODO: Maybe?
    else
        return NULL;
}

// Public Insert
// Takes care of establishing root or calling member function.
void BSTree::Insert( const Record& rec)
{
    if (root != NULL)   // Tree has already been established.
        Insert(rec, root);
    else                // Root node has not been created - current node is new root.
        root = new node(rec);
}

// Private Insert
// Recursively traverses tree and places record.
void BSTree::Insert( const Record& rec, node* current)
{
    // Find out which direction we need to traverse to get to the current
    // node's proper position.

    if (rec >= current->data)               // Go to the right.
    {
        if (current->right_child != NULL)   // Continue to the right if possible
            Insert(rec, current->right_child);
        else                                // Correct spot has been found.
            current->right_child = new node(rec);
    }

    else // rec < current->data. Go to the left.
    {
        if (current->left_child != NULL)
            Insert(rec, current->left_child);
        else
            current->left_child = new node(rec);
    }
}

void BSTree::InOrderTraversal ( void (*operate) (const Record&))
{
    if ( !IsEmpty() )
        InOrderTraversal( operate, root);
}
void BSTree::InOrderTraversal ( void (*operate) (const Record&), node* current)
{
    if (current->left_child)
        InOrderTraversal(operate, current->left_child);

    operate (root->data);

    if (current->right_child)
        InOrderTraversal(operate, current->right_child);
}

void BSTree::PreOrderTraversal ( void (*operate) (const Record&))
{
    if ( !IsEmpty() )
        PreOrderTraversal(operate, root);
}

void BSTree::PreOrderTraversal ( void(*operate) (const Record&), node* current)
{
    operate (current->data);
    if (current->left_child)
        PreOrderTraversal(operate, current->left_child);
    if (current->right_child)
        PreOrderTraversal(operate, current->right_child);
}

void BSTree::PostOrderTraversal ( void (*operate) (const Record&))
{
    if ( !IsEmpty() )
        PostOrderTraversal(operate, root);
}

void BSTree::PostOrderTraversal( void (*operate) (const Record&), node* current)
{
    if (current->left_child)
        PostOrderTraversal(operate, current->left_child);
    if (current->right_child)
        PostOrderTraversal(operate, current->right_child);
    operate(current->data);
}

unsigned BSTree::Depth ( void ) const
{
    if ( IsEmpty() ) return 0;
    else return Depth(root);
}

unsigned BSTree::Depth(node* current) const
{
    if (current == NULL) return 0;
    else
    {
        int left_depth = Depth(current->left_child);
        int right_depth = Depth(current->right_child);
        return ( (left_depth > right_depth) ? left_depth + 1 : right_depth + 1 );
    }
}

// Extra Credit.
void BSTree::Delete (const KeyType& key)
{
    if ( !IsEmpty() )
    {
        // Complicated Stuff.
    }
}