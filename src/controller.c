#include "controller.h"

void init_controller(struct controller *this, struct model *model) {
    this->model = model;
}

void handle_user_input(struct controller *this, int argc, char *argv[]) {
    if (argc < 2) {
        display_error("Usage: task-cli <command> [<args>]\n");
    }



};