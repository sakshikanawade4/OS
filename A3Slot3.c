#include <stdio.h>

#define MAX_BLOCKS 100

int blocks[MAX_BLOCKS];
int indexTable[MAX_BLOCKS];
int i;

void initializeBlocks(int n) {
    for (i = 0; i < n; i++) {
        blocks[i] = 0; // 0 indicates free block
        indexTable[i] = -1; // -1 indicates no index
    }
}

void allocateIndexedFile(int indexBlock, int fileBlocks[], int length, int n) {
    if (blocks[indexBlock] != 0) {
        printf("Error: Index block is already allocated.\n");
        return;
    }
    blocks[indexBlock] = 1; // Allocate index block
    for (i = 0; i < length; i++) {
        if (blocks[fileBlocks[i]] != 0 || fileBlocks[i] >= n) {
            printf("Error: Block %d is not free or out of range.\n", fileBlocks[i]);
            blocks[indexBlock] = 0; // Rollback index block allocation
            return;
        }
        blocks[fileBlocks[i]] = 1; // Allocate file block
        indexTable[fileBlocks[i]] = indexBlock; // Link to index block
    }
    printf("File allocated with index block %d.\n", indexBlock);
}

void displayBlocks(int n) {
    printf("Disk blocks and index table:\n");
    for (i = 0; i < n; i++) {
        printf("Block %d: %s, Index Block: %d\n", i, blocks[i] == 0 ? "Free" : "Allocated", indexTable[i]);
    }
}

int main() {
    int n, choice, indexBlock, length, fileBlocks[MAX_BLOCKS];

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
                printf("Enter the index block: ");
                scanf("%d", &indexBlock);
                printf("Enter the number of blocks in the file: ");
                scanf("%d", &length);
                printf("Enter the blocks: ");
                for (i = 0; i < length; i++) {
                    scanf("%d", &fileBlocks[i]);
                }
                allocateIndexedFile(indexBlock, fileBlocks, length, n);
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

