#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model.h"
#include "view.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

struct controller {
    struct model *model;
};

void init_controller(struct controller *this, struct model *model);
void handle_user_input(struct controller *this, int argc, char *argv[]);

#endif