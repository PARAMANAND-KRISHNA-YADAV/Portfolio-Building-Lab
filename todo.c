#include <stdio.h>
#include <string.h>

char task[100][100];   /* task names */
char when[100][20];    /* "today" or a future date */
int  done[100];        /* 0 = not done, 1 = done */
int  count = 0;

void save() {
    FILE *f = fopen("todo.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(f, "%d|%s|%s\n", done[i], when[i], task[i]);
    fclose(f);
}

void load() {
    FILE *f = fopen("todo.txt", "r");
    if (f == NULL) return;
    while (fscanf(f, "%d|%19[^|]|%99[^\n]\n", &done[count], when[count], task[count]) == 3)
        count++;
    fclose(f);
}

void add() {
    int choice;
    printf("Task: ");
    scanf(" %[^\n]", task[count]);
    printf("1. Present (today)\n2. Future\nChoose: ");
    scanf("%d", &choice);
    if (choice == 2) {
        printf("Enter date (example 25-12-2026): ");
        scanf("%s", when[count]);
    } else {
        strcpy(when[count], "today");
    }
    done[count] = 0;
    count++;
    save();
    printf("Task added!\n");
}

void show() {
    printf("\nNo  Done  When         Task\n");
    for (int i = 0; i < count; i++) {
        printf("%-3d [%c]   %-12s %s\n", i + 1, done[i] ? 'x' : ' ', when[i], task[i]);
    }
    if (count == 0) printf("No tasks yet.\n");
}

void finish() {
    int n;
    show();
    printf("Enter task number to mark done: ");
    scanf("%d", &n);
    if (n >= 1 && n <= count) {
        done[n - 1] = 1;
        save();
        printf("Task marked as done!\n");
    } else {
        printf("Wrong number.\n");
    }
}

int main() {
    int choice;
    load();
    while (1) {
        printf("\n--- TODO LIST ---\n");
        printf("1. Add task\n2. Show tasks\n3. Mark task done\n4. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice == 1) add();
        else if (choice == 2) show();
        else if (choice == 3) finish();
        else if (choice == 4) break;
        else printf("Wrong choice.\n");
    }
    return 0;
}