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
    printf("ENTER THE LENGTH: ");
    int n;
    scanf("%d", &n);

    int incomingStream[n];
    printf("ENTER THE NUMBERS IN SEQUENCE:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &incomingStream[i]);
    }

    int frames = MAX_FRAMES;
    int queue[MAX_FRAMES];
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
            int nextOccurrence[MAX_FRAMES];
            bool found = false;

            for (int j = 0; j < frames; j++) {
                nextOccurrence[j] = INT_MAX;

                for (int k = i + 1; k < n; k++) {
                    if (queue[j] == incomingStream[k]) {
                        nextOccurrence[j] = k;
                        found = true;
                        break;
                    }
                }
            }

            if (!found) {
                queue[0] = incomingStream[i];
                printFrame(queue, occupied);
                pagefault++;
            } else {
                int maxIndex = 0;
                for (int j = 1; j < frames; j++) {
                    if (nextOccurrence[j] > nextOccurrence[maxIndex]) {
                        maxIndex = j;
                    }
                }
                queue[maxIndex] = incomingStream[i];
                printFrame(queue, occupied);
                pagefault++;
            }
        }
        printf("\n");
    }
    printf("Page Fault: %d\n", pagefault);

    return 0;
}