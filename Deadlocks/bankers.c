#include <stdio.h>

#define n 5 // Number of processes
#define m 3 // Number of resources

void calculateNeed(int need[n][m], int max[n][m], int alloc[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

int main() {
    int alloc[n][m] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int max[n][m] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {4, 2, 2}, {5, 3, 3}};
    int avail[m] = {3, 3, 2};
    int f[n] = {0};
    int ans[n] = {0};
    int ind = 0;

    int need[n][m];
    calculateNeed(need, max, alloc);

    int y;
    for (int k = 0; k < n; k++) {
        f[k] = 0;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    printf("Following is the SAFE Sequence(Deadlock Avoidance):\n");
    for (int i = 0; i < n - 1; i++) {
        printf(" P%d ->", ans[i]);
    }
    printf(" P%d\n", ans[n - 1]);

    return 0;
}