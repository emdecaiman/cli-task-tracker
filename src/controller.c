#include "controller.h"

void init_controller(struct controller *this, struct model *model) {
    this->model = model;
}

void handle_user_input(struct controller *this, int argc, char *argv[]) {
    if (argc < 2) {
        display_error("Usage: task-cli <command> [<args>]\n");
        return;
    } 

    char *command = argv[1];

    if (strcmp(command, "add") == 0) {
        if (argc != 4) {
            display_error("Usage: task-cli add \"task\" \"group\"\n");
            return;
        }

        int id = add_task(this->model, argv[2], argv[3]);
        display_query_message(id, "added"); 

    } else if (strcmp(command, "update") == 0) {
        if (argc != 4) {
            display_error("Usage: task-cli update <id> \"task\"\n");
            return;
        }
        int id = atoi(argv[2]);

        display_query_message(id, "updated");

    } else if (strcmp(command, "delete") == 0) {
        if (argc != 3) {
            display_error("Usage: task-cli delete <id>\n");
            return;
        }

    } else if (strcmp(command, "mark") == 0) {
        if (argc != 3) {
            display_error("Usage: task-cli mark <id> <done><to-do><in-progress>\n");
            return;
        }
        // mark to-do
        // mark in-progress
        // mark done

    } else if (strcmp(command, "list") == 0) {
        if (argc != 3) {
            display_error("Usage: task-cli list <done><to-do><in-progress><all>\n");
            return;
        }
        list_tasks(this->model, argv[2]);
    } else {
        display_error("Error: Not a valid command\n");
    }
};