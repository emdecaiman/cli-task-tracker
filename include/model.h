#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#ifndef MODEL_H
#define MODEL_H

struct model {
    sqlite3 *db;
};

int init_model(struct model *this);
int execute_sql(struct model *this, const char *sql, int (*callback)(void *, int, char **, char **));
int add_task(struct model *this, const char *task, const char *group);
int get_group_id(struct model *this, const char *group);
int add_group(struct model *this, const char *group);
int update_task(struct model *this, int task_id, const char *task);
int get_task_id(struct model *this, int task_id);
int list_tasks(struct model *this, const char *filter);
int update_task_mark(struct model *this, int task_id, const char *task);
int delete_task(struct model *this, int task_id);

#endif
