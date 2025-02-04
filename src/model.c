#include "model.h"

#include "view.h"

// callback function is caleld on each row in the table
static int callback(void *data, int num_columns, char **column_text, char **column_name) {
    display_task(num_columns, column_text, column_name);
    return 0;
}

int execute_sql(struct model *this, const char *sql, int (*callback)(void *, int, char **, char **)) {
    char *err_msg = 0;
    int rc = sqlite3_exec(this->db, sql, callback, NULL, &err_msg);
    if (rc != SQLITE_OK) {
        display_error(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(this->db);
        return -1;
    }
    sqlite3_free(err_msg);
    return 0;
}

int init_model(struct model *this) {
    if (sqlite3_open("tasks.db", &this->db)) {
        display_error("Error: Unable to open database");
        return -1;
    }

    const char *sql_groups =
        "CREATE TABLE IF NOT EXISTS groups ("
        "group_id INTEGER PRIMARY KEY,"
        "group_name TEXT NOT NULL UNIQUE"
        ");";

    const char *sql_tasks =
        "CREATE TABLE IF NOT EXISTS tasks ("
        "task_id INTEGER PRIMARY KEY,"
        "group_id INTEGER,"
        "description TEXT NOT NULL,"
        "status TEXT CHECK(status IN ('todo', 'in-progress', 'done')) NOT NULL DEFAULT 'todo',"
        "date_created DATE DEFAULT (datetime('now', 'localtime')),"
        "FOREIGN KEY (group_id) REFERENCES groups(group_id)"
        ");";

    if (execute_sql(this, sql_tasks, NULL) != 0) {
        return -1;
    }
    if (execute_sql(this, sql_groups, NULL) != 0) {
        return -1;
    }

    return 0;
}

int add_task(struct model *this, const char *task, const char *group) {
    int group_id = get_group_id(this, group);
    char sql[256];

    snprintf(sql, sizeof(sql), "INSERT INTO tasks (group_id, description) VALUES (%d, '%s');", group_id, task);

    if (execute_sql(this, sql, NULL) != 0) {
        return -1;
    }

    int task_id = (int)sqlite3_last_insert_rowid(this->db);

    return task_id;
}

int get_group_id(struct model *this, const char *group) {
    char sql[256];

    snprintf(sql, sizeof(sql), "SELECT group_id FROM groups WHERE group_name = '%s';", group);

    struct sqlite3_stmt *stmt;

    // compile sql text into byte-code
    int rc = sqlite3_prepare_v2(this->db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        display_error("Error: sqlite3_prepare_v2");
        sqlite3_finalize(stmt);
        return -1;
    }

    int group_id;
    // checks to see if a row is returned
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        if (add_group(this, group) != 0) {
            sqlite3_finalize(stmt);
            return -1;
        }
        group_id = (int)sqlite3_last_insert_rowid(this->db);
    } else {
        group_id = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return group_id;
}

int add_group(struct model *this, const char *group) {
    char sql[256];

    snprintf(sql, sizeof(sql), "INSERT INTO groups (group_name) VALUES ('%s');", group);

    return execute_sql(this, sql, NULL);
}


int update_task(struct model *this, int task_id, const char *task) {
    if (get_task_id(this, task_id) != 0) {
        return -1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql),
             "UPDATE tasks "
             "SET description = '%s' "
             "WHERE task_id = %d;",
             task, task_id);
    return execute_sql(this, sql, NULL);
}

int get_task_id(struct model *this, int task_id) {
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT task_id FROM tasks WHERE task_id = %d;", task_id);

    struct sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(this->db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        display_error("Error: sqlite3_prepare_v2");
        sqlite3_finalize(stmt);
        return -1;
    }

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

int list_tasks(struct model *this, const char *filter) {
    int isValidFilter = strcmp(filter, "done") == 0 
        || strcmp(filter, "todo") == 0 
        || strcmp(filter, "in-progress") == 0;
    char sql[256];

    if (strcmp(filter, "all") == 0) {
        char *sql_all = 
            "SELECT task_id, group_name, description, status, date_created "
            "FROM tasks "
            "INNER JOIN groups ON tasks.group_id = groups.group_id;";
        strcpy(sql, sql_all);

    } else if (isValidFilter) {
        snprintf(sql, sizeof(sql),
                "SELECT task_id, group_name, description, status, date_created "
                "FROM tasks "
                "INNER JOIN groups ON tasks.group_id = groups.group_id "
                "WHERE status = '%s';",
                filter);
    } else {
        display_error("Usage: task-cli list <done><todo><in-progress><all>");
        return -1;
    }
    return execute_sql(this, sql, callback);
}

int update_task_mark(struct model *this, int task_id, const char *task) {
    int isValidTask = strcmp(task, "done") == 0
        || strcmp(task, "todo") == 0
        || strcmp(task, "in-progress") == 0;

    if (get_task_id(this, task_id) != 0 || !isValidTask) {
        return -1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql),
            "UPDATE tasks "
            "SET status = '%s' "
            "WHERE task_id = %d;",
            task, task_id);
    return execute_sql(this, sql, NULL);
}
