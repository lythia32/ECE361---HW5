/**
 * bst.h -h file for binary tree
 *
 * @file:       bst.h
 * @author:		Shelly Vu (vshelly@pdx.edu
 *
 * Defines a BST for storing temperature, humidity, and timestamp data,
 * with functions to create, insert, search, traverse, and delete nodes.
 *
 */

#ifndef BST_H
#define BST_H

#include <time.h>
#include <stdint.h>

/**
 * temp_humid_data - Stores temperature and humidity information.
 *
 * Holds a timestamp, temperature, and humidity for a single record.
 */
struct temp_humid_data {
    time_t timestamp;
    uint32_t temp;
    uint32_t humid;
};

/**
 * bst_node - Represents a node in the Binary Search Tree (BST).
 *
 * Contains temperature and humidity data and pointers to child nodes.
 */
typedef struct bst_node {
    struct temp_humid_data data;
    struct bst_node* left;
    struct bst_node* right;
} bst_node;

/**
 * createbst_node - Creates a new BST node.
 *
 * Allocates memory and initializes a node with the given data.
 *
 * @param data: The temperature and humidity data to store in the node.
 * @return Pointer to the newly created node, or NULL if allocation fails.
 */
bst_node* createbst_node(struct temp_humid_data data);


/**
 * insertbst_node - Adds a node to the BST.
 *
 * Inserts data into the tree based on the timestamp value.
 *
 * @param root: Pointer to the root of the tree.
 * @param data: The data to add to the tree.
 * @return Pointer to the updated root of the tree.
 */
bst_node* insertbst_node(bst_node* root, struct temp_humid_data data);


/**
 * searchBST - Searches for a node in the BST.
 *
 * Looks for a specific timestamp in the tree.
 *
 * @param root: Pointer to the root of the tree.
 * @param timestamp: The timestamp to find.
 * @return Pointer to the data if found, or NULL if not found.
 */
struct temp_humid_data* searchBST(bst_node* root, time_t timestamp);


/**
 * traversal - Prints all nodes in the BST.
 *
 * Visits each node in order and displays its data.
 *
 * @param root: Pointer to the root of the tree.
 */
void traversal(bst_node* root);


/**
 * delete_bst - Frees all memory used by the BST.
 *
 * Deletes all nodes in the tree.
 *
 * @param root: Pointer to the root of the tree.
 */
void delete_bst(bst_node* root);

#endif // BST_H
