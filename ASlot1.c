#include <stdio.h>

void displayMatrix(int matrix[][3], int rows, const char *name) {
	int i,j;
    printf("%s Matrix:\n", name);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
	int i,j;
    int allocation[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int available[3];
    int need[5][3];

    // Accept available resources
    printf("Enter available resources (A B C): ");
    for (i = 0; i < 3; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate the need matrix
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Display Allocation Matrix
    displayMatrix(allocation, 5, "Allocation");

    // Display Max Matrix
    displayMatrix(max, 5, "Max");

    // Display Need Matrix
    displayMatrix(need, 5, "Need");

    // Display Available Resources
    printf("Available Resources:\n");
    for (i = 0; i < 3; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    return 0;
}
