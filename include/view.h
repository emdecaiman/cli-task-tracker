#ifndef VIEW_H
#define VIEW_H

void display_error(char *error_msg);
void display_query_message(int id, char *query);
void display_list();
void display_task(int num_columns, char **column_text, char **column_name);
void display_message(char *string);

#endif
