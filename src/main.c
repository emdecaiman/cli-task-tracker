#include "controller.h"
#include "model.h"
#include "view.h"

int main(int argc, char *argv[]) {
    struct controller controller;
    struct model model;

    init_model(&model);
    init_controller(&controller, &model);
    handle_user_input(&controller, argc, argv);
    sqlite3_close(model.db); 

    return 0;
}