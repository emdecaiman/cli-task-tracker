#include "model.h"
#include "view.h"

void execute_sql(struct model *this, const char *sql, int (*callback)(void*, int, char**, char**)) {
    char *err_msg = 0;
    int rc = sqlite3_exec(this->db, sql, callback, 0, &err_msg);
    if ( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        display_error("Error: Unable to create tables");
        sqlite3_free(err_msg);
        sqlite3_close(this->db); 
        exit(EXIT_FAILURE);
    } 
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

