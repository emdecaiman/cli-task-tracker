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
        if (id == -1) {
            display_error("Error: Unable to add task\n");
            return;
        }
        display_query_message(id, "added");

    } else if (strcmp(command, "update") == 0) {
        if (argc != 4) {
            display_error("Usage: task-cli update <id> \"task\"\n");
            return;
        }
        int task_id = atoi(argv[2]);

        if (update_task(this->model, task_id, argv[3]) != 0) {
            display_error("Error: Unable to update task\n");
            return;
        }
        display_query_message(task_id, "updated");

    } else if (strcmp(command, "delete") == 0) {
        if (argc != 3) {
            display_error("Usage: task-cli delete <id>\n");
            return;
        }

        // to do still

    } else if (strcmp(command, "mark") == 0) {
        if (argc != 3) {
            display_error("Usage: task-cli mark <id> <done><todo><in-progress>\n");
            return;
        }
        // mark to-do
        // mark in-progress
        // mark done

    } else if (strcmp(command, "list") == 0) {
        if (argc != 3) {
            display_error("Usage: task-cli list <done><todo><in-progress><all>\n");
            return;
        }
        if (list_tasks(this->model, argv[2]) != 0) {
            display_error("Error: Unable to list task\n");
        }
    } else {
        display_error("Error: Not a valid command\n");
    }
};