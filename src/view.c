#include "view.h"
#include <stdio.h>

void display_error(char *error_msg) {
    fprintf(stderr, "%s", error_msg); 
}

void display_query_message(int id, char *query) {
    printf("Task %s successfully (ID: %d)\n", query, id);
};