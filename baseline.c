// Baseline implementation using linked list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MESSAGE_LEN 64

typedef struct LogNode {
    char level[16];
    char message[MESSAGE_LEN];
    struct LogNode *next;
} LogNode;

LogNode *create_log(const char *level, const char *message) {
    LogNode *node = malloc(sizeof(LogNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    strcpy(node->level, level);
    strcpy(node->message, message);
    node->next = NULL;
    return node;
}

void append_log(LogNode **head, LogNode **tail, const char *level, const char *message) {
    LogNode *node = create_log(level, message);

    if (*head == NULL) {
        *head = node;
        *tail = node;
    } else {
        (*tail)->next = node;
        *tail = node;
    }
}

int count_errors(LogNode *head) {
    int count = 0;
    while (head != NULL) {
        if (strcmp(head->level, "ERROR") == 0) {
            count++;
        }
        head = head->next;
    }
    return count;
}

int count_duplicate_errors(LogNode *head) {
    int duplicates = 0;

    for (LogNode *current = head; current != NULL; current = current->next) {
        if (strcmp(current->level, "ERROR") != 0) {
            continue;
        }

        for (LogNode *check = current->next; check != NULL; check = check->next) {
            if (strcmp(check->level, "ERROR") == 0 &&
                strcmp(current->message, check->message) == 0) {
                duplicates++;
                break;
            }
        }
    }

    return duplicates;
}

void free_logs(LogNode *head) {
    while (head != NULL) {
        LogNode *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char *argv[]) {
    int size = 100000;

    if (argc > 1) {
        size = atoi(argv[1]);
    }

    if (size <= 0) {
        fprintf(stderr, "Input size must be positive\n");
        return 1;
    }

    LogNode *head = NULL;
    LogNode *tail = NULL;

    clock_t start = clock();

    for (int i = 0; i < size; i++) {
        if (i % 5 == 0) {
            append_log(&head, &tail, "ERROR", "Database connection failed");
        } else if (i % 3 == 0) {
            append_log(&head, &tail, "WARN", "High memory usage");
        } else {
            append_log(&head, &tail, "INFO", "Request completed");
        }
    }

    int errors = count_errors(head);
    int duplicate_errors = count_duplicate_errors(head);

    clock_t end = clock();

    double elapsed_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("Baseline linked-list implementation\n");
    printf("Log entries processed: %d\n", size);
    printf("Total ERROR logs: %d\n", errors);
    printf("Duplicate ERROR logs: %d\n", duplicate_errors);
    printf("Execution time: %.3f ms\n", elapsed_ms);

    free_logs(head);

    return 0;
}