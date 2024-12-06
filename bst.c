/**
 * bst.c -C file for binary tree
 *
 * @file:       bst.c
 * @author:		Shelly Vu (vshelly@pdx.edu)
 *
 * This code implements a Binary Search Tree (BST) for storing and managing temperature, humidity, and timestamp data.
 * It includes functions for creating, inserting, searching, and traversing nodes, as well as
 * deleting the entire tree to free memory. The traversal function displays data in ascending order.
 *
 */

#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * createbst_node() - Creates a new BST node.
 *
 * Allocates memory for a new node and sets its data and child pointers.
 *
 * @param data: The data (timestamp, temperature, and humidity) for the node.
 *
 * @return A pointer to the new node, or NULL if memory allocation fails.
 */

bst_node* createbst_node(struct temp_humid_data data) {
    bst_node* node = (bst_node*)malloc(sizeof(bst_node));
    if (node) {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

/**
 * insertbst_node() - Inserts data into the BST.
 *
 * Adds a new node to the BST based on its timestamp value.
 *
 * @param root: Pointer to the root of the tree.
 * @param data: The data to insert into the tree.
 *
 * @return The updated root of the tree.
 */
bst_node* insertbst_node(bst_node* root, struct temp_humid_data data) {
    if (!root) {
        return createbst_node(data);
    }
    if (data.timestamp < root->data.timestamp) {
        root->left = insertbst_node(root->left, data);
    } else if (data.timestamp > root->data.timestamp) {
        root->right = insertbst_node(root->right, data);
    }
    return root;
}

/**
 * searchBST() - Finds a node in the BST.
 *
 * Looks for a node by its timestamp in the tree.
 *
 * @param root: Pointer to the root of the tree.
 * @param timestamp: The timestamp to search for.
 *
 * @return Pointer to the node's data if found, or NULL if not found.
 */
struct temp_humid_data* searchBST(bst_node* root, time_t timestamp) {
    if (!root) return NULL;
    if (timestamp == root->data.timestamp) {
        return &root->data;
    }
    if (timestamp < root->data.timestamp) {
        return searchBST(root->left, timestamp);
    }
    return searchBST(root->right, timestamp);
}


/**
 * traversal() - Displays all nodes in the BST.
 *
 * Visits each node in ascending order and prints its data.
 *
 * @param root: Pointer to the root of the tree.
 */
void traversal(bst_node* root) {
    if (!root) return;

    traversal(root->left);

    // format the date
    char formatted_date[20];
    struct tm* tm_info = localtime(&root->data.timestamp);
    strftime(formatted_date, sizeof(formatted_date), "%d-%b-%Y", tm_info);

    // calc temp & humidity
    float temp_f = root->data.temp / 1.0;
    float humid_percent = root->data.humid / 1.0;

    // print format same as professor
    printf("%s     %.1fF(%08X) %.1f%%(%08X)\n",
           formatted_date,
           temp_f, root->data.temp,
           humid_percent, root->data.humid);

    traversal(root->right);
}

/**
 * delete_bst() - Deletes all nodes in the BST.
 *
 * Frees memory for all nodes in the tree.
 *
 * @param root: Pointer to the root of the tree.
 */
void delete_bst(bst_node* root) {
    if (!root) return;
    delete_bst(root->left);
    delete_bst(root->right);
    free(root);
}
