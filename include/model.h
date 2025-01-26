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
int add_task(struct model *this, const char *task, const char *group);
int get_group_id(struct model *this, const char *group);
void add_group(struct model *this, const char* group);


#endif