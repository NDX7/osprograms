#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int n, m;

bool check(int i) {
    for (int j = 0; j < m; j++) {
        if (need[i][j] > available[j]) {
            return false;
        }
    }
    return true;
}

int main() {
    printf("Enter the number of Processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);
    printf("Enter the number of Resources (max %d): ", MAX_RESOURCES);
    scanf("%d", &m);

    // Input allocation matrix
    for (int i = 0; i < n; i++) {
        printf("\nEnter the number of instances allocated for Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input max matrix
    for (int i = 0; i < n; i++) {
        printf("\nEnter Max matrix entry for Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("\nEnter the number of instances available of Resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    char sequence[MAX_PROCESSES][4]; // Increased size to accommodate "P0", "P1", etc.
    int visited[MAX_PROCESSES] = {0};
    int count = 0;

    while (count < n) {
        bool safe = false;
        for (int i = 0; i < n; i++) {
            if (visited[i] == 0 && check(i)) {
                sprintf(sequence[count], "P%d", i);
                count++;
                visited[i] = 1;
                safe = true;

                // Update available resources
                for (int j = 0; j < m; j++) {
                    available[j] += allocation[i][j];
                }
            }
        }
        if (!safe) {
            break; // No safe process found
        }
    }

    // Check if the system is in a safe state
    if (count < n) {
        printf("The System is Unsafe!\n");
    } else {
        printf("\nThe System is Safe!\n");
        printf("Safe Sequence is: ");
        for (int i = 0; i < n; i++) {
            printf("%s ", sequence[i]);
        }
        printf("\nAvailable resources are: ");
        for (int i = 0; i < m; i++) {
            printf("%d ", available[i]);
        }
        printf("\n");
    }

    return 0;
}
