#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[50];
    int priority;      // higher value = higher priority
    int completed;     // 0 = pending, 1 = done
} Task;

Task tasks[MAX];
int taskCount = 0;

// Function Prototypes
void addTask();
void displayTasks();
void executeNext();
void saveToFile();
void loadFromFile();
void deleteTask();
void searchTask();
void sortByPriority();

// Main Menu
int main() {
    int choice;

    loadFromFile(); // Auto-load previous tasks

    while (1) {
        printf("\n==============================\n");
        printf("     MINI TASK SCHEDULER\n");
        printf("==============================\n");
        printf("1. Add Task\n");
        printf("2. Show All Tasks\n");
        printf("3. Execute Next Task (Highest Priority)\n");
        printf("4. Search Task\n");
        printf("5. Delete Task\n");
        printf("6. Save Tasks\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: addTask(); break;
        case 2: displayTasks(); break;
        case 3: executeNext(); break;
        case 4: searchTask(); break;
        case 5: deleteTask(); break;
        case 6: saveToFile(); break;
        case 7: 
            saveToFile();
            printf("Goodbye!\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Add a new task
void addTask() {
    if (taskCount >= MAX) {
        printf("Task list full!\n");
        return;
    }
    Task t;
    t.id = taskCount + 1;
    printf("Enter task name: ");
    getchar();
    fgets(t.name, 50, stdin);
    t.name[strcspn(t.name, "\n")] = 0;

    printf("Enter priority (1-10): ");
    scanf("%d", &t.priority);

    t.completed = 0;

    tasks[taskCount++] = t;
    sortByPriority();

    printf("Task added successfully!\n");
}

// Show all tasks
void displayTasks() {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n%-5s %-20s %-10s %-10s\n", "ID", "Task", "Priority", "Status");
    for (int i = 0; i < taskCount; i++) {
        printf("%-5d %-20s %-10d %-10s\n",
               tasks[i].id, tasks[i].name, tasks[i].priority,
               tasks[i].completed ? "Done" : "Pending");
    }
}

// Execute highest priority task
void executeNext() {
    if (taskCount == 0) {
        printf("No tasks to execute!\n");
        return;
    }

    printf("Executing task: %s (Priority %d)\n",
           tasks[0].name, tasks[0].priority);

    tasks[0].completed = 1;

    // Remove it by shifting
    for (int i = 1; i < taskCount; i++) {
        tasks[i - 1] = tasks[i];
    }
    taskCount--;

    printf("Task executed and removed from queue.\n");
}

// Save tasks to file
void saveToFile() {
    FILE *f = fopen("tasks.txt", "w");
    if (!f) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(f, "%d|%s|%d|%d\n",
                tasks[i].id, tasks[i].name,
                tasks[i].priority, tasks[i].completed);
    }

    fclose(f);
    printf("Tasks saved.\n");
}

// Load tasks from file
void loadFromFile() {
    FILE *f = fopen("tasks.txt", "r");
    if (!f) return;

    taskCount = 0;

    while (!feof(f)) {
        Task t;
        if (fscanf(f, "%d|%49[^|]|%d|%d\n",
                   &t.id, t.name, &t.priority, &t.completed) == 4) {
            tasks[taskCount++] = t;
        }
    }
    fclose(f);
    sortByPriority();
}

// Delete a task
void deleteTask() {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    int id;
    printf("Enter task ID to delete: ");
    scanf("%d", &id);

    int found = 0;

    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            found = 1;
            for (int j = i; j < taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            taskCount--;
            printf("Task deleted.\n");
            return;
        }
    }

    if (!found)
        printf("Task not found!\n");
}

// Search task by keyword
void searchTask() {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    char key[50];
    printf("Enter keyword: ");
    getchar();
    fgets(key, 50, stdin);
    key[strcspn(key, "\n")] = 0;

    printf("\nSearch results:\n");
    for (int i = 0; i < taskCount; i++) {
        if (strstr(tasks[i].name, key)) {
            printf("ID: %d | %s | Priority: %d\n",
                   tasks[i].id, tasks[i].name, tasks[i].priority);
        }
    }
}

// Sort tasks by priority (highest first)
void sortByPriority() {
    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            if (tasks[j].priority < tasks[j + 1].priority) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}
