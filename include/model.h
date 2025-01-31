#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef MODEL_H
#define MODEL_H

struct model {
    sqlite3 *db;
};

void init_model(struct model *this);
void execute_sql(struct model *this, const char *sql, int (*callback)(void *, int, char **, char **));
int add_task(struct model *this, const char *task, const char *group);
int get_group_id(struct model *this, const char *group);
void add_group(struct model *this, const char *group);
void update_task(struct model *this, int task_id, const char *task);
void list_tasks(struct model *this, const char *filter);

#endif