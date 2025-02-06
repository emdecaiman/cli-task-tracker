# CLI Task Tracker 
A simple command line interface (CLI) to track and manage your tasks. This application is written
in C and uses SQLite database.

## Commands
This application supports the following commands
```sh
# Adding a task into a category
task-cli add "task" "category"

# Updating a task description
task-cli update <id> "task"

# Deleting a task
task-cli delete <id>

# Marking a task as in-progress, done, or todo
task-cli mark <id> <done><todo><in-progress>

# Listing tasks
task-cli list <done><todo><in-progress><all>
```
## Installation
```sh
git clone https://github.com/yourusername/cli-task-tracker.git
cd cli-task-tracker
make
```
You can add an alias for the executable to run the program from any directory. To do so, first modify line 25 in model.c `char db_path[512] = "/PATH/tasks.db";` replacing with your absolute path. Then edit your ~/.zshrc or ~/.bashrc file and add the following `alias task-cli='/PATH/task-cli`. After restarting your terminal, you should be able to run `task-cli` from any directory.
