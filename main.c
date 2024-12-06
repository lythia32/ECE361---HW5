/**
 * main.c -c file for HW5
 *
 * @file:       main.c
 * @author:		Shelly Vu (vshelly@pdx.edu)
 *
 *
 * Implements a program to store, search, and display temperature and humidity data
 * using a Binary Search Tree (BST), with randomized insertion and user queries.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "bst.h"
#include "iom361_r2.h"

// struct to hold temp & humidity range
typedef struct {
    float temp_low;
    float temp_high;
    float humid_low;
    float humid_high;
} temp_humid_range;

// function prototypes
void shuffle_indices(int* indices, int size);
void log_search(bst_node* node);
void format_timestamp(time_t timestamp, char* buffer);
struct temp_humid_data* search_timestamp(bst_node* root, time_t timestamp, void (*log_search)(bst_node* node));
temp_humid_range get_range_th(int month);
bst_node* populate_bst(bst_node* root, int month, int day, int num_days);

// get average temp & humidity ranges for a given month
temp_humid_range get_range_th(int month) {
    temp_humid_range range;

    // define temp & humidity ranges based on the month
    switch (month) {
        // jan - dec = ranges from ChatGPT
        case 1: range.temp_low = 36.0; range.temp_high = 46.0; range.humid_low = 75.0; range.humid_high = 90.0; break;
        case 2: range.temp_low = 38.0; range.temp_high = 51.0; range.humid_low = 70.0; range.humid_high = 85.0; break;
        case 3: range.temp_low = 41.0; range.temp_high = 56.0; range.humid_low = 65.0; range.humid_high = 80.0; break;
        case 4: range.temp_low = 44.0; range.temp_high = 62.0; range.humid_low = 60.0; range.humid_high = 75.0; break;
        case 5: range.temp_low = 49.0; range.temp_high = 69.0; range.humid_low = 55.0; range.humid_high = 70.0; break;
        case 6: range.temp_low = 53.0; range.temp_high = 74.0; range.humid_low = 50.0; range.humid_high = 65.0; break;
        case 7: range.temp_low = 57.0; range.temp_high = 82.0; range.humid_low = 45.0; range.humid_high = 60.0; break;
        case 8: range.temp_low = 57.0; range.temp_high = 83.0; range.humid_low = 45.0; range.humid_high = 60.0; break;
        case 9: range.temp_low = 53.0; range.temp_high = 76.0; range.humid_low = 50.0; range.humid_high = 65.0; break;
        case 10: range.temp_low = 47.0; range.temp_high = 64.0; range.humid_low = 60.0; range.humid_high = 75.0; break;
        case 11: range.temp_low = 41.0; range.temp_high = 52.0; range.humid_low = 70.0; range.humid_high = 85.0; break;
        case 12: range.temp_low = 36.0; range.temp_high = 45.0; range.humid_low = 75.0; range.humid_high = 90.0; break;
        default: range.temp_low = 36.0; range.temp_high = 46.0; range.humid_low = 75.0; range.humid_high = 90.0; break;
    }

    return range;
}

// func - shuffle function for randomizing array indices
void shuffle_indices(int* indices, int size) {
    if (size > 1) {
        for (int i = 0; i < size - 1; i++) {
            int j = i + rand() / (RAND_MAX / (size - i) + 1);
            int temp = indices[j];
            indices[j] = indices[i];
            indices[i] = temp;
        }
    }
}

// func - log visited nodes during search
void log_search(bst_node* node) {
    if (node) {
        printf("-> [%lld] %s", (long long)node->data.timestamp, ctime(&(node->data.timestamp)));
        // please note that fflush after printf is needed for mobaxterm to run
        // till this day, I don't know why
        fflush(stdout);
    }
}

// func - format timestamp to readable str
void format_timestamp(time_t timestamp, char* buffer) {
    struct tm* tm_info = localtime(&timestamp);
    strftime(buffer, 30, "%a %b %d %H:%M:%S %Y", tm_info);
}

// func - search BST with logging
struct temp_humid_data* search_timestamp(bst_node* root, time_t timestamp, void (*log_search)(bst_node* node)) {
    // start from root of the BST
    bst_node* current = root;
    while (current) {
        // log current node being visited
        log_search(current);

        // traverse left
        if (timestamp < current->data.timestamp) {
            current = current->left;
        }
        // traverse right
        else if (timestamp > current->data.timestamp) {
            current = current->right;
        }
        // match = return data
        else {
            return &(current->data);
        }
    }
    // not found
    return NULL;
}

// funct - populate BST w/ temper & humidity
bst_node* populate_bst(bst_node* root, int month, int day, int num_days) {
    if (num_days <= 0) {
        printf("ERROR: Number of days must be greater than zero.\n");
        fflush(stdout);
        return root;
    }

    // allocate memory
    struct temp_humid_data* records = malloc(num_days * sizeof(struct temp_humid_data));
    int* indices = malloc(num_days * sizeof(int));
    if (!records || !indices) {
        fprintf(stderr, "ERROR: Failed to allocate memory for records or indices.\n");
        fflush(stdout);
        free(records);
        free(indices);
        return root;
    }

    // get temp & humidity range for month
    temp_humid_range range = get_range_th(month);

    struct tm date = {0};
    // year = 2023
    date.tm_year = 2023 - 1900;
    // set month start at 0
    date.tm_mon = month - 1;
    // set start day
    date.tm_mday = day;

    // generate temp & humidity records
    for (int i = 0; i < num_days; i++) {
        // random temp & humidity
        float temp = range.temp_low + (rand() / (float)RAND_MAX) * (range.temp_high - range.temp_low);
        float humid = range.humid_low + (rand() / (float)RAND_MAX) * (range.humid_high - range.humid_low);

        // convert date timestamp
        time_t current_time = mktime(&date);
        records[i].timestamp = current_time;
        records[i].temp = (uint32_t)temp;
        records[i].humid = (uint32_t)humid;

        // assign index for every day I'm shufflinggggg (please get this reference)
        indices[i] = i;
        date.tm_mday++;
        mktime(&date);
    }

    // random number
    srand((unsigned int)time(NULL));
    shuffle_indices(indices, num_days);

    // insert records into bst in randomized order
    for (int i = 0; i < num_days; i++) {
        int idx = indices[i];
        printf("INFO(main()): added timestamp %lld from data[%d] to BST\n", (long long)records[idx].timestamp, idx);
        fflush(stdout);
        root = insertbst_node(root, records[idx]);
    }

    // freee memory
    free(records);
    free(indices);
    return root;
}

// func - main
int main() {
    bst_node* root = NULL;
    int month, day, num_days;

    printf("Welcome! Temperature & Humidity of 2023 here we go!\n");
    fflush(stdout);
    printf("Enter the starting month (1 to 12),day (1 to 31), and number of days (1 to 100): ");
    fflush(stdout);
    if (scanf("%d,%d,%d", &month, &day, &num_days) != 3) {
        printf("ERROR: Invalid input format. Please use 'MM,DD,NUM_DAYS'.\n");
        fflush(stdout);
        return 1;
    }

    printf("User requested %d data items starting at %2d/%2d/2023\n", num_days, month, day);
    fflush(stdout);

    root = populate_bst(root, month, day, num_days); // Populate the BST with data
    if (!root) {
        printf("No data was added to the BST.\n");
        fflush(stdout);
        return 1;
    }

    getchar(); // Clear input buffer
    char search_date[20];
    printf("\nEnter a search date (mm/dd/yyyy): ");
    fflush(stdout);
    while (fgets(search_date, sizeof(search_date), stdin)) {
        search_date[strcspn(search_date, "\n")] = 0;

        if (strlen(search_date) == 0) break;

        struct tm search_tm = {0};
        time_t search_time;

        // Parse the search date into a timestamp
        if (sscanf(search_date, "%2d/%2d/%4d", &search_tm.tm_mon, &search_tm.tm_mday, &search_tm.tm_year) == 3) {
            search_tm.tm_year -= 1900;
            search_tm.tm_mon -= 1;
            search_time = mktime(&search_tm);

            printf("INFO(search()): Starting search for timestamp %lld\n", (long long)search_time);
            fflush(stdout);

            struct temp_humid_data* result = search_timestamp(root, search_time, log_search);

            if (result) {
                char formatted_date[30];
                format_timestamp(result->timestamp, formatted_date);
                printf("FOUND-> %s\n", formatted_date);
                printf("%s     %.1fF(%08X) %.1f%%(%08X)\n",
                       formatted_date,
                       result->temp / 1.0, result->temp,
                       result->humid / 1.0, result->humid);
                fflush(stdout);
            } else {
                printf("Did not find data for Timestamp %s\n", search_date);
                fflush(stdout);
            }
        } else {
            printf("Invalid date format. Please use mm/dd/yyyy.\n");
            fflush(stdout);
        }

        printf("\nEnter a search date (mm/dd/yyyy): ");
        fflush(stdout);
    }

    printf("\nINFO(main()): End search for data items in BST\n");
    printf("\nTemperature/Humidity table:\n");
    printf("---------------------------\n");
    fflush(stdout);
    // perform an inorder traversal from bst.h
    traversal(root);

    // free memory from bst.h
    delete_bst(root);
    printf("\n");
    fflush(stdout);
    printf("Thank you!\nExiting program.\n");
    fflush(stdout);
    return 0;
}
