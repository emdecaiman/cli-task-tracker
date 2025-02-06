#include "controller.h"

void init_controller(struct controller *this, struct model *model) {
    this->model = model;
}

void handle_user_input(struct controller *this, int argc, char *argv[]) {
    if (argc < 2) {
        display_error("Usage: task-cli <command> [<args>]");
        return;
    }

    char *command = argv[1];

    if (strcmp(command, "add") == 0) {
        if (argc != 4) {
            display_error("Usage: task-cli add \"task\" \"group\"");
            return;
        }

        int id = add_task(this->model, argv[2], argv[3]);
        if (id == -1) {
            display_error("Error: Unable to add task\n");
            display_error("Usage: task-cli add \"task\" \"group\"");
            return;
        }
        display_query_message(id, "added");

    } else if (strcmp(command, "update") == 0) {
        if (argc != 4) {
            display_error("Usage: task-cli update <id> \"task\"");
            return;
        }
        int task_id = atoi(argv[2]);

        if (update_task(this->model, task_id, argv[3]) != 0) {
            display_error("Error: Unable to update task");
            display_error("Usage: task-cli update <id> \"task\"");
            return;
        }
        display_query_message(task_id, "updated");

    } else if (strcmp(command, "delete") == 0) {
        if (argc != 3) {
            display_error("Usage: task-cli delete <id>");
            return;
        }

        if (user_confirmation_input() != 0) {
            return;
        }

        int task_id = atoi(argv[2]);
        if (delete_task(this->model, task_id) != 0) {
            display_error("Error: Unable to delete task");
            display_error("Usage: task-cli delete <id>");
            return;
        }
        display_query_message(task_id, "deleted");
    } else if (strcmp(command, "mark") == 0) {
        if (argc != 4) {
            display_error("Usage: task-cli mark <id> <done><todo><in-progress>");
            return;
        }

        int task_id = atoi(argv[2]);
        if (update_task_mark(this->model, task_id, argv[3]) != 0) {
            display_error("Error: Unable to mark task");
            display_error("Usage: task-cli mark <id> <done><todo><in-progress>");
            return;
        }
        display_query_message(task_id, "marked");

    } else if (strcmp(command, "list") == 0) {
        if (argc != 3) {
            display_error("Usage: task-cli list <done><todo><in-progress><all>");
            return;
        }
        if (list_tasks(this->model, argv[2]) != 0) {
            display_error("Error: Unable to list task");
            display_error("Usage: task-cli list <done><todo><in-progress><all>");
        }
    } else {
        display_error("Error: Not a valid command");
    }
};

int user_confirmation_input() {
    char input;

    display_message("Notice: Confirm deletion <y><n>");
    scanf("%c", &input);

    if (input == 'y') {
        return 0;
    } else if (input == 'n') {
        return 1;
    }

    display_message("Notice: Confirm deletion <y><n>");

    return -1;
}





