#include "view.h"

#include <stdio.h>

void display_error(char *error_msg) {
    fprintf(stderr, "%s", error_msg);
}

void display_query_message(int id, char *query) {
    printf("Task %s successfully (ID: %d)\n", query, id);
};

void display_task(int num_columns, char **column_text, char **column_name) {
    static int column_names_printed = 0;

    if (!column_names_printed) {
        for (int i = 0; i < num_columns; i++) {
            if (i == num_columns - 1) {
                printf("%s", column_name[i]);
            } else {
                printf("%s | ", column_name[i]);
            }
        }
        printf("\n");
        column_names_printed = 1;
    }

    for (int i = 0; i < num_columns; i++) {
        if (i == num_columns - 1) {
            printf("%s", column_text[i]);
        } else {
            printf("%s | ", column_text[i]);
        }
    }
    printf("\n");
}
