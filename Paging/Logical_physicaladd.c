#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 10

struct PageTableEntry {
    int pageNumber;
    int frameNumber;
};

struct PageTableEntry pageTable[10];

int convert(int virtualAddress) {
    int pageNumber = virtualAddress / PAGE_SIZE;
    int offset = virtualAddress % PAGE_SIZE;

    int frameNumber = -1;
    for (int i = 0; i < 10; i++) {
        if (pageTable[i].pageNumber == pageNumber) {
            frameNumber = pageTable[i].frameNumber;
            break;
        }
    }

    if (frameNumber == -1) {
        printf("Page Fault\n");
        return -1;
    }

    return frameNumber * PAGE_SIZE + offset;
}

int main() {
    printf("Enter the No. of Entries for Page Table: ");
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter the index(0-9) and Value((0-30)*10): ");
        scanf("%d %d", &pageTable[i].pageNumber, &pageTable[i].frameNumber);
    }

    int choice = 0;
    while (choice != 2) {
        printf("\nEnter 1 to convert VA to PA\n");
        printf("Enter 2 to exit\n");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter the VA: ");
            int VA;
            scanf("%d", &VA);
            printf("The PA is = %d\n", convert(VA));
        } else {
            printf("Enter Again\n");
        }
    }

    return 0;
}
