// Optimized implementation using contiguous array storage

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MESSAGE_LEN 64

typedef struct {
    char level[16];
    char message[MESSAGE_LEN];
} LogRecord;

void generate_logs(LogRecord *logs, int size) {
    for (int i = 0; i < size; i++) {
        if (i % 5 == 0) {
            strcpy(logs[i].level, "ERROR");
            strcpy(logs[i].message, "Database connection failed");
        } else if (i % 3 == 0) {
            strcpy(logs[i].level, "WARN");
            strcpy(logs[i].message, "High memory usage");
        } else {
            strcpy(logs[i].level, "INFO");
            strcpy(logs[i].message, "Request completed");
        }
    }
}

int count_errors(LogRecord *logs, int size) {
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (strcmp(logs[i].level, "ERROR") == 0) {
            count++;
        }
    }

    return count;
}

int count_duplicate_errors(LogRecord *logs, int size) {
    int duplicates = 0;
    int seen_database_error = 0;

    for (int i = 0; i < size; i++) {
        if (strcmp(logs[i].level, "ERROR") == 0 &&
            strcmp(logs[i].message, "Database connection failed") == 0) {
            if (seen_database_error) {
                duplicates++;
            } else {
                seen_database_error = 1;
            }
        }
    }

    return duplicates;
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

    LogRecord *logs = malloc(sizeof(LogRecord) * size);

    if (!logs) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    clock_t start = clock();

    generate_logs(logs, size);

    int errors = count_errors(logs, size);
    int duplicate_errors = count_duplicate_errors(logs, size);

    clock_t end = clock();

    double elapsed_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("Optimized array-based implementation\n");
    printf("Log entries processed: %d\n", size);
    printf("Total ERROR logs: %d\n", errors);
    printf("Duplicate ERROR logs: %d\n", duplicate_errors);
    printf("Execution time: %.3f ms\n", elapsed_ms);

    free(logs);

    return 0;
}