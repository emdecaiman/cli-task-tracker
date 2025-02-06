#include "controller.h"
#include "model.h"
#include "view.h"

int main(int argc, char *argv[]) {
    struct controller controller;
    struct model model;

    if (init_model(&model) != 0 ) {
        display_error("Error: Unable to initialize model");
        return 1;
    }
    init_controller(&controller, &model);
    handle_user_input(&controller, argc, argv);
    sqlite3_close(model.db);

    return 0;
}
