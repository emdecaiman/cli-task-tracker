#include <sqlite3.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MODEL_H
#define MODEL_H

struct model {
    sqlite3 *db;
};

void init_model(struct model *this);
void execute_sql(struct model *this, const char *sql, int (*callback)(void*, int, char**, char**));



#endif