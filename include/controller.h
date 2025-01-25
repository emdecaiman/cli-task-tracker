#include "model.h"
#include "view.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef CONTROLLER_H
#define CONTROLLER_H

struct controller {
    struct model *model;
};

void init_controller(struct controller *this, struct model *model);
void handle_user_input(struct controller *this, int argc, char *argv[]);


#endif