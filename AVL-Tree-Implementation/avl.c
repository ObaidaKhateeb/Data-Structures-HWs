#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

/****
  Student1 name:Obaeda Khatib
  Student2 name: Mohammad Mhneha

  Student1 ID: 201278066
  Student2 ID: 315649814
****/


AVLNodePtr leftRotate(AVLNodePtr root);
AVLNodePtr rightRotate(AVLNodePtr root);
AVLNodePtr min_value_tree(AVLNodePtr root);
int rank(AVLNodePtr root);
int height(AVLNodePtr root);
int Balance(AVLNodePtr root);
AVLNodePtr Rotations(AVLNodePtr root);
void swapBetweenNodes(AVLNodePtr node1, AVLNodePtr node2);
AVLNodePtr successor(AVLNodePtr root, int x);
AVLNodePtr predecessor(AVLNodePtr root, int x);
int lesser_nodes(AVLNodePtr root, AVLNodePtr node);
AVLNodePtr find_node_by_position(AVLNodePtr root, int position);
AVLNodePtr merge(AVLNodePtr root1, AVLNodePtr root2);
AVLNodePtr split(AVLNodePtr root, int x, AVLNodePtr trees_out[2]);


//preforms left rotate
AVLNodePtr leftRotate(AVLNodePtr root)
{
    //from the lecture
    //taking the right child of root and left child of the right child,and change the childern pointers
    AVLNodePtr right = root->child[1];
    AVLNodePtr right_l = right->child[0];
    if (right == NULL)
        return root;



    right->child[0] = root;
    root->child[1] = right_l;


    root->height = height(root);
    right->height = height(right);
    root->rank = rank(root);
    right->rank = rank(right);


    return right;
}

AVLNodePtr rightRotate(AVLNodePtr root)
{
    AVLNodePtr left = root->child[0]; // Store the left child of the root
    AVLNodePtr left_r = left->child[1]; // Store the right child of the left child
    AVLNodePtr pa = root->parent; // Store the parent of the root

    // Perform the right rotation
    left->child[1] = root; // Make the left child's right child the new root
    root->child[0] = left_r; // Make the original root the left child of its previous left child

    if (left_r != NULL)
    {
        left_r->parent = root; // Update the parent pointer of the right child of the left child
    }
    root->parent = left; // Update the parent pointer of the root
    left->parent = pa; // Update the parent pointer of the new root
    left->height = height(left); // Recalculate the height of the new root
    root->height = height(root); // Recalculate the height of the original root
    root->rank = rank(root); // Recalculate the rank of the original root
    left->rank = rank(left); // Recalculate the rank of the new root
    return left; // Return the new root
}


int _max(int x, int y)
{
    return (x < y) ? y : x; // Return the maximum of two values
}


int _abs(int x)
{
    return (x < 0) ? -x : x; // Return the absolute value of an integer
}


void submitters()
{
    // Print the names and IDs of the submitters
    printf("Obaeda Khatib\n201278066\nMohammad Mhneha \n315649814");
    return; // Return from the function
}

// take the minimum of a given tree
AVLNodePtr min_value_tree(AVLNodePtr root)
{
    AVLNodePtr temp = root;
    while (temp->child[0] != NULL)
    {
        temp = temp->child[0];
    }
    return temp;
}
//return the rank of a certain node ,adding the left child rank and the rank of the right child and return it 
int rank(AVLNodePtr root)
{
    if (root == NULL)
        return 0;
    else if ((root->child[0] == NULL) && (root->child[1] == NULL))
        return 1;
    else if ((root->child[0] == NULL) || (root->child[1] == NULL))
        return 2;
    else if (root->child[0] != NULL && root->child[1] != NULL)
        return root->child[0]->rank + root->child[1]->rank + 1;
}

// calculate the height and return it
int height(AVLNodePtr root)
{
    if (root == NULL)
        return -1;
    else if ((root->child[0] == NULL) && (root->child[1] == NULL))// node is a leaf
        return 0;
    else if ((root->child[0] == NULL))
        return root->child[1]->height + 1;
    else if ((root->child[1] == NULL))
        return root->child[0]->height + 1;
    return (root->child[0]->height > root->child[1]->height) ? root->child[0]->height + 1 : root->child[1]->height + 1;

}
// binary search 
// compare the root key with a given node and determine to go left or right 
AVLNodePtr avl_search(AVLNodePtr root, int x, int y)
{

    if (root == NULL || root->key == x && root->y == y)
    {
        return root;
    }
    if (root->key > x)
    {
        return avl_search(root->child[0], x, y);
    }
    else
    {
        return avl_search(root->child[1], x, y);
    }

}

// check balance factor
int Balance(AVLNodePtr root)
{
    int left, right;
    left = (root && root->child[0]) ? root->child[0]->height : -1;
    right = (root && root->child[1]) ? root->child[1]->height : -1;
    return left - right;

}
// decide which rotation to do
AVLNodePtr Rotations(AVLNodePtr root)
{

    int temp = Balance(root);


    //LL 
    if (temp > 1 && Balance(root->child[0]) >= 0)
    {
        return rightRotate(root);
    }
    //LR
    if (temp > 1 && Balance(root->child[0]) < 0)
    {
        root->child[0] = leftRotate(root->child[0]);
        return rightRotate(root);
    }

    //RR
    if (temp < -1 && Balance(root->child[1]) <= 0)
    {
        return leftRotate(root);
    }

    //RL
    if (temp < -1 && Balance(root->child[1]) > 0)
    {
        root->child[1] = rightRotate(root->child[1]);
        return leftRotate(root);
    }


    return root;
}




// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
// Inserts a node with key 'x' and value 'y' into the AVL tree.
AVLNodePtr avl_insert(AVLNodePtr root, int x, int y)
{
    if (root == NULL)
    {
        root = new_avl_node(x, y);
        return root;
    }

    if (root->key == x)
    {
        return root; // Node with the same key already exists, return without inserting.
    }

    if (root->key > x)
    {
        root->child[0] = avl_insert(root->child[0], x, y); // Recursively insert into the left subtree.
        root->parent = root->child[0]; // Update the parent pointer.
    }
    else if (root->key < x)
    {
        root->child[1] = avl_insert(root->child[1], x, y); // Recursively insert into the right subtree.
        root->parent = root->child[1]; // Update the parent pointer.
    }

    root->height = height(root); // Update the height of the current node.
    root->rank = rank(root); // Update the rank of the current node.
    root = Rotations(root); // Perform necessary rotations to balance the tree.

    return root;
}

// Deletes the node with key 'x' and value 'y' from the AVL tree.
AVLNodePtr avl_delete(AVLNodePtr root, int x, int y)
{
    if (root == NULL)
    {
        return root; // Node not found, return without any changes.
    }

    if (root->key > x)
    {
        root->child[0] = avl_delete(root->child[0], x, y); // Recursively delete from the left subtree.
    }
    else if (root->key < x)
    {
        root->child[1] = avl_delete(root->child[1], x, y); // Recursively delete from the right subtree.
    }
    else if (root->key == x && root->y == y)
    {
        if (root->child[0] == NULL || root->child[1] == NULL)
        {
            // Node has at most one child.
            AVLNodePtr temp = root->child[0] ? root->child[0] : root->child[1];

            if (temp == NULL) // No child case
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            {
                *root = *temp; // Copy the child node to the current node.
            }

            free(temp); // Free the memory of the deleted node.
        }
        else // Node has two children
        {
            // Find the minimum value node in the right subtree and replace the current node with it.
            AVLNodePtr temp1 = min_value_tree(root->child[1]);
            root->key = temp1->key;
            root->y = temp1->y;

            root->child[1] = avl_delete(root->child[1], temp1->key, temp1->y); // Delete the duplicate node.
        }
    }

    if (root == NULL)
    {
        return root; // Tree is empty after deletion.
    }

    root->height = height(root); // Update the height of the current node.
    root->rank = rank(root); // Update the rank of the current node.
    root = Rotations(root); // Perform necessary rotations to balance the tree.

    return root;
}

// Swaps the pointers between two nodes.
void swapBetweenNodes(AVLNodePtr node1, AVLNodePtr node2)
{
    AVLNodePtr temp;
    // Swapping between the two nodes in the child's field of their parents.
    if (node1->parent != NULL)
    {
        if (node1->parent->key < node1->key)
        {
            node1->parent->child[1] = node2;
        }
        else
        {
            node1->parent->child[0] = node2;
        }
    }
    node2->parent->child[0] = node1;
    // Swapping between the parents of the two nodes.
    temp = node1->parent;
    node1->parent = node2->parent;
    node2->parent = temp;
    // Swapping between the two nodes in the parent's field of their children.
    node1->child[0]->parent = node2;
    node1->child[1]->parent = node2;
    if (node2->child[1] != NULL)
    {
        node2->child[1]->parent = node1;
    }
    // Swapping between the children of the two nodes.
    temp = node1->child[0];
    node1->child[0] = node2->child[0];
    node2->child[0] = temp;
    temp = node1->child[1];
    node1->child[1] = node2->child[1];
    node2->child[1] = temp;
    // Recounting the new height and rank of each node.
    node1->height = height(node1);
    node2->height = height(node2);
    node1->rank = rank(node1);
    node2->rank = rank(node2);
}

// Creates a new AVL node with key 'x' and value 'y'.
AVLNodePtr new_avl_node(int x, int y)
{
    struct AVLNode* node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    if (node != NULL)
    {
        node->key = x;
        node->y = y;
        node->child[0] = NULL;
        node->child[1] = NULL;
        node->parent = NULL;
        node->height = 0;
        node->rank = 1;
        return node;
    }
    else
    {
        printf("malloc failed"); // Error message if memory allocation fails.
        return NULL;
    }
}

// Deletes all nodes in the AVL tree.
void delete_avl_tree(AVLNodePtr root)
{
    if (root == NULL)
        return;

    delete_avl_tree(root->child[0]);  // Recursively delete the left subtree
    delete_avl_tree(root->child[1]);  // Recursively delete the right subtree
    free(root);                       // Free the memory allocated for the current node
    return;
}




//function that search and return the node which key value is the smallest greater than the given x.
AVLNodePtr successor(AVLNodePtr root, int x)
{
    struct AVLNode* temp;
    if (root != NULL)
    {
        if (root->key == x)
        {
            return root;
        }
        else if (root->key < x)
        {
            return successor(root->child[1], x);  // Search in the right subtree
        }
        else if (root->key > x)
        {
            temp = successor(root->child[0], x);  // Search in the left subtree
            if (temp == NULL)
            {
                return root;  // Current root is the successor
            }
            else
            {
                return temp;  // Successor found in the left subtree
            }
        }
    }
    return NULL;  // Key 'x' not found in the AVL tree
}

//function that search and return the node which key value is the largest smaller than the given x. 
AVLNodePtr predecessor(AVLNodePtr root, int x)
{
    struct AVLNode* temp;
    if (root != NULL)
    {
        if (root->key == x) // Check if the root node has the same key as the target key
        {
            return root;
        }
        else if (root->key < x) // If the root key is less than the target key
        {
            temp = predecessor(root->child[1], x); // Recursively search in the right subtree
            if (temp == NULL)
            {
                return root; // If no predecessor found in the right subtree, the root is the predecessor
            }
            else
            {
                return temp; // Otherwise, return the result obtained from the recursive call
            }
        }
        else if (root->key > x) // If the root key is greater than the target key
        {
            return predecessor(root->child[0], x); // Recursively search in the left subtree
        }
    }
    return NULL; // Return NULL if the root is NULL or no predecessor found
}

int lesser_nodes(AVLNodePtr root, AVLNodePtr node)
{
    if (root != NULL)
    {
        if (root == node) // Check if the current root node is the target node
        {
            if (root->child[0] == NULL) // If the target node has no left child
            {
                return 1; // Return 1, as there are no lesser nodes in the tree
            }
            else
            {
                return 1 + root->child[0]->rank; // Return the rank of the left child, representing the number of lesser nodes
            }
        }
        if (root->key > node->key) // If the root key is greater than the target node's key
        {
            return lesser_nodes(root->child[0], node); // Recursively search in the left subtree
        }
        else if (root->key < node->key) // If the root key is less than the target node's key
        {
            if (root->child[0] == NULL) // If the left child is NULL
                return 1 + lesser_nodes(root->child[1], node); // Return 1 plus the number of lesser nodes in the right subtree
            return 1 + root->child[0]->rank + lesser_nodes(root->child[1], node); // Return the rank of the left child plus the number of lesser nodes in the right subtree
        }
    }
    return 0; // Return 0 if the root is NULL or no lesser nodes found
}

AVLNodePtr find_node_by_position(AVLNodePtr root, int position)
{
    if (root->child[0] == NULL) // If the left child is NULL
    {
        if (position == 0) // If the position is 0, indicating the root node
        {
            return root; // Return the root node
        }
        else if (position == 1) // If the position is 1, indicating the right child
        {
            return root->child[1]; // Return the right child
        }
    }
    else if (root->child[0]->rank == position) // If the rank of the left child is equal to the position
    {
        return root; // Return the current root node
    }
    else if (root->child[0]->rank < position) // If the rank of the left child is less than the position
    {
        // Search in the right subtree with the updated position
        return find_node_by_position(root->child[1], position - root->child[0]->rank - 1);
        // Subtract the rank of the left child plus 1 from the position to find the updated position in the right subtree
    }
    else if (root->child[0]->rank > position) // If the rank of the left child is greater than the position
    {
        // Search in the left subtree with the same position
        return find_node_by_position(root->child[0], position);
    }
    return NULL; // Return NULL if the root is NULL or no node found at the specified position
}

// Function to merge two AVL trees into a single AVL tree
AVLNodePtr merge(AVLNodePtr root1, AVLNodePtr root2)
{
    // If either tree is empty, return the other tree as the result
    if (root1 == NULL)
    {
        return root2;
    }
    if (root2 == NULL)
    {
        return root1;
    }

    AVLNodePtr newRoot;
    // Compare the root keys to determine the new root
    if (root1->key < root2->key)
    {
        newRoot = root1;
        newRoot->child[1] = merge(root1->child[1], root2);
    }
    else
    {
        newRoot = root2;
        newRoot->child[0] = merge(root1, root2->child[0]);
    }

    // Update height and rank of the new root
    newRoot->height = height(newRoot);
    newRoot->rank = rank(newRoot);

    // Perform rotations to maintain AVL tree properties
    return Rotations(newRoot);
}

// Function to split a given tree into two trees based on a given key value
AVLNodePtr split(AVLNodePtr root, int x, AVLNodePtr trees_out[2])
{
    AVLNodePtr newRoot;

    // If the root is empty, return NULL
    if (root == NULL)
    {
        return NULL;
    }

    // If the root key matches the given key, split the tree
    if (root->key == x)
    {
        trees_out[0] = root->child[0];
        trees_out[1] = root->child[1];
        return root;
    }
    // If the root key is greater than the given key, traverse the left subtree
    else if (root->key > x)
    {
        newRoot = split(root->child[0], x, trees_out);
    }
    // If the root key is less than the given key, traverse the right subtree
    else
    {
        newRoot = split(root->child[1], x, trees_out);
    }

    // Insert the root into the appropriate subtree based on the key comparison
    if (root->key > x)
    {
        root->child[1] = avl_insert(root->child[1], root->key, root->y);
        trees_out[1] = merge(trees_out[1], root->child[1]);
    }
    else
    {
        root->child[0] = avl_insert(root->child[0], root->key, root->y);
        trees_out[0] = merge(trees_out[0], root->child[0]);
    }

    return newRoot;
}


//function that accept a tree, and two integers: x1 and x2, finds and returns the number of the nodes that their key values in the range between x1 and x2, and delete the middle third of these nodes.
int delete_third(AVLNodePtr root, int x1, int x2)
{
    int numOfNodes, lesserthanfirst, lesserthanlast;
    AVLNodePtr tree1, tree2, tree3, newTree, first, last, deleteFirst, deleteSecond;
    AVLNodePtr arr1[2], arr2[2];
    AVLNode temp2;

    // Find the first and last nodes within the given range
    first = successor(root, x1);
    last = predecessor(root, x2);

    // If either first or last is NULL, there are no nodes in the given range
    if (first == NULL || last == NULL)
    {
        return 0;
    }

    // Count the number of nodes in the range
    lesserthanfirst = lesser_nodes(root, first);
    lesserthanlast = lesser_nodes(root, last);
    numOfNodes = lesserthanlast - lesserthanfirst + 1;

    // If the number of nodes is less than 3, there's no middle third to delete
    if (numOfNodes < 3)
    {
        return 0;
    }

    // Find the nodes to delete in the middle third
    deleteFirst = find_node_by_position(root, lesserthanfirst + (numOfNodes / 3) - 1);
    deleteSecond = find_node_by_position(root, lesserthanlast - (numOfNodes / 3) - 1);

    // Split the tree into three parts: tree1, tree2, tree3
    split(root, deleteFirst->key, arr1);
    tree1 = arr1[0];
    tree2 = arr1[1];
    split(tree2, deleteSecond->key, arr2);
    tree2 = arr2[0];
    tree3 = arr2[1];

    // Delete tree2 (middle third of the nodes)
    delete_avl_tree(tree2);

    // Merge tree1 and tree3 to form the new tree
    newTree = merge(tree1, tree3);

    // Swap the contents of the new tree with the original root
    temp2 = *root;
    *root = *newTree;
    *newTree = temp2;

    // Free the memory occupied by the new tree
    free(newTree);

    // Return the number of nodes in the range
    return numOfNodes;
}