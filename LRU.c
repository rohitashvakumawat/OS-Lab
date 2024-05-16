#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_FRAMES 3

bool checkHit(int incomingPage, int queue[], int occupied) {
    for (int i = 0; i < occupied; i++) {
        if (incomingPage == queue[i])
            return true;
    }
    return false;
}

void printFrame(int queue[], int occupied) {
    for (int i = 0; i < occupied; i++)
        printf("%d\t\t\t", queue[i]);
}

int main() {
    printf("Enter the length of incoming stream: ");
    int n;
    scanf("%d", &n);

    int incomingStream[n];
    printf("Enter the numbers in sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &incomingStream[i]);
    }

    int frames = MAX_FRAMES;
    int queue[MAX_FRAMES];
    int distance[MAX_FRAMES];
    int occupied = 0;
    int pagefault = 0;

    printf("Page\t Frame1 \t Frame2 \t Frame3\n");

    for (int i = 0; i < n; i++) {
        printf("%d: \t\t", incomingStream[i]);

        if (checkHit(incomingStream[i], queue, occupied)) {
            printFrame(queue, occupied);
        } else if (occupied < frames) {
            queue[occupied] = incomingStream[i];
            pagefault++;
            occupied++;
            printFrame(queue, occupied);
        } else {
            int max = INT_MIN;
            int index = -1;
            for (int j = 0; j < frames; j++) {
                distance[j] = 0;
                for (int k = i - 1; k >= 0; k--) {
                    ++distance[j];
                    if (queue[j] == incomingStream[k])
                        break;
                }
                if (distance[j] > max) {
                    max = distance[j];
                    index = j;
                }
            }
            queue[index] = incomingStream[i];
            printFrame(queue, occupied);
            pagefault++;
        }
        printf("\n");
    }
    printf("Page Fault: %d\n", pagefault);

    return 0;
}
