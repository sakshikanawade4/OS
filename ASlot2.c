#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int processes, resources,i,j,p,k;


// Function to calculate the Need matrix
void calculateNeed() {
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Safety algorithm
bool isSafe() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    for (i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    while (count < processes) {
        bool found = false;
        for (p = 0; p < processes; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (j = 0; j < resources; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (k = 0; k < resources; k++) {
                        work[k] += allocation[p][k];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("The system is NOT in a safe state.\n");
            return false;
        }
    }

    printf("The system is in a safe state.\nSafe Sequence: ");
    for (i = 0; i < processes; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

// Resource request algorithm
bool resourceRequest(int process, int request[]) {
    for (i = 0; i < resources; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Error: Resources are not available.\n");
            return false;
        }
    }

    // Temporarily allocate resources
    for (i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the system is still in a safe state
    if (isSafe()) {
        printf("Request granted.\n");
        return true;
    } else {
        // Rollback
        for (i = 0; i < resources; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        printf("Request cannot be granted as it leads to an unsafe state.\n");
        return false;
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the Allocation matrix:\n");
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Maximum matrix:\n");
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Available resources:\n");
    for (i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    calculateNeed();

    printf("The Need matrix is:\n");
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    if (isSafe()) {
        printf("Initial state is safe.\n");
    } else {
        printf("Initial state is NOT safe.\n");
        return 0;
    }

    while (true) {
        int process;
        printf("Enter the process number making the request (-1 to exit): ");
        scanf("%d", &process);

        if (process == -1) {
            break;
        }

        int request[MAX_RESOURCES];
        printf("Enter the request for process %d:\n", process);
        for (i = 0; i < resources; i++) {
            scanf("%d", &request[i]);
        }

        resourceRequest(process, request);
    }

    return 0;
}

