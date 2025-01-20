#include <stdio.h>

#define MAX_BLOCKS 100

int blocks[MAX_BLOCKS];
int links[MAX_BLOCKS];
int i;

void initializeBlocks(int n) {
    for (i = 0; i < n; i++) {
        blocks[i] = 0; // 0 indicates free block
        links[i] = -1; // -1 indicates no link
    }
}

void allocateLinkedFile(int start, int length, int n) {
    if (blocks[start] != 0) {
        printf("Error: Starting block is already allocated.\n");
        return;
    }
    int count = 0, prev = -1, current = start;
    while (count < length) {
        if (current >= n || blocks[current] != 0) {
            printf("Error: Insufficient free blocks available.\n");
            return;
        }
        blocks[current] = 1; // Mark as allocated
        if (prev != -1) {
            links[prev] = current;
        }
        prev = current;
        count++;
        current++;
    }
    printf("File allocated starting at block %d.\n", start);
}

void displayBlocks(int n) {
    printf("Disk blocks and links:\n");
    for (i = 0; i < n; i++) {
        printf("Block %d: %s, Link: %d\n", i, blocks[i] == 0 ? "Free" : "Allocated", links[i]);
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
                allocateLinkedFile(start, length, n);
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

