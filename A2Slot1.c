#include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 100

int blocks[MAX_BLOCKS];
int i;

void initializeBlocks(int n) {
    for (i = 0; i < n; i++) {
        blocks[i] = 0; // 0 indicates free block
    }
}

void allocateSequentialFile(int start, int length, int n) {
    if (start + length > n) {
        printf("Error: Not enough space in disk to allocate the file.\n");
        return;
    }
    for (i = start; i < start + length; i++) {
        if (blocks[i] != 0) {
            printf("Error: Block %d is already allocated.\n", i);
            return;
        }
    }
    for (i = start; i < start + length; i++) {
        blocks[i] = 1; // Mark as allocated
    }
    printf("File allocated from block %d to block %d.\n", start, start + length - 1);
}

void displayBlocks(int n) {
    printf("Disk blocks status:\n");
    for (i = 0; i < n; i++) {
        printf("Block %d: %s\n", i, blocks[i] == 0 ? "Free" : "Allocated");
    }
}

int main() {
    int n, choice, start, length;

    printf("Enter the number of blocks in the disk: ");
    scanf("%d", &n);

    initializeBlocks(n);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Allocate file\n");
        printf("2. Display blocks\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the starting block and length of the file: ");
                scanf("%d %d", &start, &length);
                allocateSequentialFile(start, length, n);
                break;
            case 2:
                displayBlocks(n);
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

