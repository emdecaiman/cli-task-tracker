#include "model.h"
#include "view.h"

void execute_sql(struct model *this, const char *sql, int (*callback)(void*, int, char**, char**)) {
    char *err_msg = 0;
    int rc = sqlite3_exec(this->db, sql, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        display_error(err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(this->db); 
        exit(EXIT_FAILURE);
    } 
    sqlite3_free(err_msg);
}

void init_model(struct model *this) {
    if (sqlite3_open("tasks.db", &this->db)) {
        display_error("Error: Unable to open database");
        exit(EXIT_FAILURE);
    }

    const char *sql_groups =
        "CREATE TABLE IF NOT EXISTS groups ("\
        "group_id INTEGER PRIMARY KEY,"\
        "group_name TEXT NOT NULL UNIQUE"\
        ");";

    const char *sql_tasks = 
        "CREATE TABLE IF NOT EXISTS tasks ("\
        "task_id INTEGER PRIMARY KEY,"\
        "group_id INTEGER,"\
        "description TEXT NOT NULL,"\
        "status TEXT CHECK(status IN ('TODO', 'IN_PROG', 'DONE')) NOT NULL DEFAULT 'TODO',"\
        "date_created DATE DEFAULT CURRENT_TIMESTAMP,"\
        "due_date DATE,"\
        "FOREIGN KEY (group_id) REFERENCES groups(group_id)"\
        ");";
    
    execute_sql(this, sql_tasks, NULL); 
    execute_sql(this, sql_groups, NULL); 
}

int add_task(struct model *this, const char *task, const char* group) {
    int group_id = get_group_id(this, group);
    printf("%d", group_id);
}

int get_group_id(struct model *this, const char* group) {
    char sql[256];
    int group_id;

    snprintf(sql, sizeof(sql), "SELECT group_id FROM groups WHERE group_name = '%s';", group);

    struct sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(this->db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        display_error("Error: sqlite3_prepare_v2");
        sqlite3_finalize(stmt);
        return -1;
    }

    if (sqlite3_step(stmt) != SQLITE_ROW) { 
        add_group(this, group);
        group_id = (int)sqlite3_last_insert_rowid(this->db);
    } else {
        group_id = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return group_id;
}

void add_group(struct model *this, const char* group) {
    char sql[256];
    
    snprintf(sql, sizeof(sql), "INSERT INTO groups (group_name) VALUES ('%s');", group);

    execute_sql(this, sql, NULL);
}