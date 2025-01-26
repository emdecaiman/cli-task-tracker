#include "controller.h"

void init_controller(struct controller *this, struct model *model) {
    this->model = model;
}

void handle_user_input(struct controller *this, int argc, char *argv[]) {
    if (argc < 2) {
        display_error("Usage: task-cli <command> [<args>]\n");
    } 

    char *command = argv[1];

    if (strcmp(command, "add") == 0) {
        if (argc != 4) {
            display_error("Usage: task-cli add \"task\" \"group\"\n");
            return;
        }

        int id = add_task(this->model, argv[2], argv[3]);
        display_query_message(id, "added"); 
        printf("%d", argc);
    } else if (strcmp(command, "update") == 0) {
        if (argc != 4) {
            display_error("Usage: task-cli update <id> \"task\"\n");
            return;
        }
        // notify model to update task
        int id = atoi(argv[2]);
        display_query_message(id, "updated");
    } else if (strcmp(command, "mark") == 0) {
        // mark in-progress
        // mark done

    } else if (strcmp(command, "list") == 0) {
        // list done
        // list todo
        // list in-progress
        // list all
    } else {
        display_error("Error: Not a valid command\n");
    }

    sqlite3_close(this->model->db); 
};