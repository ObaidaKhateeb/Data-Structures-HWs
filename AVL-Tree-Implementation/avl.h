#ifndef AVL_H
#define AVL_H

// DO NOT ADD OR REMOVE ANYTHING FROM THIS FILE

typedef enum Position {LEFT, RIGHT} Position;

typedef struct AVLNode * AVLNodePtr;

// Use only this struct definition.
typedef struct AVLNode{
    AVLNodePtr child[2]; // child[0] is left, child[1] is right.
	AVLNodePtr parent; 
    int key, height, y, rank;
} AVLNode;


// Utilities
// this function prints both submitters names and ids in this format:
// name student1 : NAME
// id student1: ID
// name student2 : NAME
// id student2: ID
void submitters();

// return the maximum of x and y.
int _max( int x, int y );

// return the absolute value of x.
int _abs( int x );

// AVL Operations and Queries

// search for a node with key <x> in the and return the node if exists. Otherwise returns NULL.
AVLNodePtr avl_search( AVLNodePtr root, int x, int y );

// insert a new node with key <x> into the subtree. If the key exists do nothing. Returns a pointer to root of the tree.
AVLNodePtr avl_insert( AVLNodePtr root, int x, int y );

// delete the node with key <x> (if exists). Returns a pointer to the root of the tree.
AVLNodePtr avl_delete( AVLNodePtr root, int x, int y );

// return the maximum y value (x,y) such that x1<x<x2
int delete_third( AVLNodePtr root, int x1, int x2 );


// return a new initialized avl node with key <x>. Returns NULL if malloc fails.
AVLNodePtr new_avl_node( int x, int y );

// Free all nodes in the tree.
void delete_avl_tree( AVLNodePtr root );


#endif
