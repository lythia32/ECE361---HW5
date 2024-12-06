#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

void log_visited_nodes(bst_node* node) {
    if (node) {
        printf("-> [%lld] %s", (long long)node->data.timestamp, ctime(&(node->data.timestamp)));
        fflush(stdout);
    }
}

int tmain() {
    printf("=== BST ADT Test Program ===\n\n");
    fflush(stdout);

    bst_node* root = NULL;

    // test case 1: insert into an empty tree
    printf("Test Case 1: Insert into an empty tree\n");
    fflush(stdout);

    // current timestamp, temp: 25, humidity: 60
    struct temp_humid_data data1 = {time(NULL), 25, 60};
    root = insertbst_node(root, data1);
    printf("Root node inserted: Temp = %u, Humidity = %u\n\n", data1.temp, data1.humid);
    fflush(stdout);

    // Test Case 2: insert multiple nodes
    printf("Test Case 2: Insert multiple nodes\n");
    fflush(stdout);

    struct temp_humid_data data2[] = {
        {time(NULL) - 86400, 20, 55},
        {time(NULL) + 86400, 30, 65},
        {time(NULL) + 2 * 86400, 35, 70},
    };

    for (int i = 0; i < 3; i++) {
        root = insertbst_node(root, data2[i]);
        printf("INFO(main): Added node with Temp = %u, Humidity = %u\n", data2[i].temp, data2[i].humid);
        fflush(stdout);
    }

    printf("Inorder Traversal:\n");
    fflush(stdout);
    traversal(root);
    printf("\n");
    fflush(stdout);

    // test case 3: search for an existing node
    printf("Test Case 3: Search for an existing node\n");
    fflush(stdout);

    // searching for the last inserted node
    struct temp_humid_data* found_data = searchBST(root, data2[2].timestamp);
    if (found_data) {
        printf("Found: Temp = %u, Humidity = %u\n\n", found_data->temp, found_data->humid);
        fflush(stdout);
    } else {
        printf("Error: Node not found.\n\n");
        fflush(stdout);
    }

    // test case 4: search for a non-existing node
    printf("Test Case 4: Search for a non-existing node\n");
    fflush(stdout);

    // 10 days
    time_t non_existing_timestamp = time(NULL) + 10 * 86400;
    found_data = searchBST(root, non_existing_timestamp);
    if (!found_data) {
        printf("Correctly handled: Node not found.\n\n");
        fflush(stdout);
    } else {
        printf("Error: Node should not exist.\n\n");
        fflush(stdout);
    }

    // test case 5: empty tree traversal
    printf("Test Case 5: Empty tree traversal\n");
    fflush(stdout);

    // deleting all nodes in the tree
    delete_bst(root);
    root = NULL;
    printf("Tree deleted. Attempting inorder traversal on empty tree:\n");
    fflush(stdout);
    // traversing an empty tree should produce no output
    traversal(root);
    printf("\n");
    fflush(stdout);

    printf("=== BST ADT Test Complete ===\n");
    fflush(stdout);
    return 0;
}
