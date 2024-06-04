#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

void calculate_difference(int request[], int head, int diff[][2], int n) { 
    for (int i = 0; i < n; i++) { 
        diff[i][0] = abs(head - request[i]); 
    }
}

int find_MIN(int diff[][2], int n) { 
    int index = -1; 
    int minimum = INT_MAX; 
    for (int i = 0; i < n; i++) { 
        if (!diff[i][1] && minimum > diff[i][0]) { 
            minimum = diff[i][0]; 
            index = i; 
        } 
    } 
    return index;
}

void shortestSeekTimeFirst(int request[], int head, int n) { 
    if (n == 0) { 
        return; 
    } 
    int diff[n][2]; 
    for (int i = 0; i < n; i++) { 
        diff[i][1] = 0; 
    } 
    int seek_count = 0; 
    int seek_sequence[n + 1]; 
    for (int i = 0; i < n; i++) { 
        seek_sequence[i] = head;
        calculate_difference(request, head, diff, n); 
        int index = find_MIN(diff, n); 
        diff[index][1] = 1; 
        seek_count += diff[index][0]; 
        head = request[index]; 
    } 
    seek_sequence[n] = head; 
    printf("Total number of seek operations = %d\n", seek_count); 
}

int main() { 
    int n, head; 
    printf("Enter the number of requests: "); 
    scanf("%d", &n); 
    int *proc = (int *)malloc(n * sizeof(int)); 
    if (proc == NULL) { 
        printf("Memory allocation failed.\n"); 
        return 1; 
    } 
    printf("Enter the request array:\n"); 
    for (int i = 0; i < n; i++) { 
        scanf("%d", &proc[i]); 
    } 
    printf("Enter the initial position of the disk head: "); 
    scanf("%d", &head); 
    shortestSeekTimeFirst(proc, head, n); 
    free(proc); 
    return 0;
}