include <stdio.h>

#define MAX_PROC 100
#define MAX_RES 100

int arrmax[MAX_PROC][MAX_RES];
int alloc[MAX_PROC][MAX_RES];
int need[MAX_PROC][MAX_RES];
int avail[MAX_RES];
int n, r;

void input() {
    printf("Enter the no of Processes: ");
    scanf("%d", &n);
    printf("Enter the no of resource instances: ");
    scanf("%d", &r);

    printf("Enter the Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &arrmax[i][j]);
        }
    }

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the available Resources:\n");
    for (int j = 0; j < r; j++) {
        scanf("%d", &avail[j]);
    }
}

void show() {
    printf("Process\t Allocation\t Max\t Available\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t ", i + 1);
        for (int j = 0; j < r; j++) {
            printf("%d ", alloc[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < r; j++) {
            printf("%d ", arrmax[i][j]);
        }
        printf("\t ");
        if (i == 0) {
            for (int j = 0; j < r; j++)
                printf("%d ", avail[j]);
        }
        printf("\n");
    }
}

void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = arrmax[i][j] - alloc[i][j];
        }
    }
}

void cal() {
    int finish[MAX_PROC] = {0};
    int dead[MAX_PROC] = {0};
    int flag = 1;
    int safe[MAX_PROC] = {0};

    calculateNeed();

    while (flag == 1) {
        flag = 0;
        for (int i = 0; i < n; i++) {
            int c = 0;
            for (int j = 0; j < r; j++) {
                if ((finish[i] == 0) && (need[i][j] <= avail[j])) {
                    c++;
                    if (c == r) {
                        for (int k = 0; k < r; k++) {
                            avail[k] += alloc[i][j];
                            finish[i] = 1;
                            flag = 1;
                        }

                        if (finish[i] == 1) {
                            i = n;
                        }
                    }
                }
            }
        }
    }

    int j = 0;
    flag = 0;
    for (int i = 0; i < n; i++) {
        if (finish[i] == 0) {
            dead[j] = i;
            j++;
            flag = 1;
        }
    }

    if (flag == 1) {
        printf("\nSystem is in Deadlock and the Deadlock process are\n");
        for (int i = 0; i < n; i++) {
            printf("P%d\t", dead[i] + 1);
        }
    } else {
        printf("\nNo Deadlock Occurs\n");
    }
}

int main() {
    printf("********** Deadlock Detection Algorithm ************\n");
    input();
    show();
    cal();
    return 0;
}
