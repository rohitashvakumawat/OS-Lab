#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id, bt, at, ct, tat, wt;
};

void input(struct Process *p, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time for process %d:\n", i + 1);
        scanf("%d", &p[i].at);
        printf("\nEnter burst time for process %d:\n", i + 1);
        scanf("%d", &p[i].bt);
        p[i].id = i + 1;
    }
}

void calc(struct Process *p, int n) {
    int sum = 0;
    sum = sum + p[0].at;
    for (int i = 0; i < n; i++) {
        sum = sum + p[i].bt;
        p[i].ct = sum;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        if (i < n - 1 && sum < p[i + 1].at) {
            int t = p[i + 1].at - sum;
            sum = sum + t;
        }
    }
}

void sort(struct Process *p, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void show(struct Process *p, int n) {
    printf("Process\tArrival\tBurst\tCompletion\tTurn Around\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf(" P%d\t %d\t%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

void ganntchart(struct Process *p, int n) {
    printf("---------"
            "---------"
            "---------\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d  ", p[i].id);
    }
    printf("|\n");
    printf("---------"
            "---------"
            "---------\n");
    printf("%d\t", p[0].at);
    for (int i = 0; i < n; i++) {
        printf("%d\t", p[i].ct);
    }
}

int main() {
    int n;
    printf("\nEnter the no of processes in your system:\n");
    scanf("%d", &n);
    struct Process *p = (struct Process *)malloc(n * sizeof(struct Process));
         
    input(p, n);
    sort(p, n);
    calc(p, n);
    show(p, n);
    ganntchart(p, n);

    free(p);
    return 0;
}
