#include <stdio.h>
#include <stdlib.h>
#define SIZE 8


void FCFS(int arr[], int head, int size) { 
    int seek_count = 0; 
    int distance, cur_track; 
    for (int i = 0; i < size; i++) { 
        cur_track = arr[i]; 
        distance = abs(cur_track - head); 
        seek_count += distance; 
        head = cur_track; 
    } 
    printf("Total number of seek operations = %d\n", seek_count);
}

int main() { 
    int head; 
    printf("Enter the initial position of the disk head: "); 
    scanf("%d", &head); 
    int arr[SIZE]; 
    printf("Enter the request array (%d elements):\n", SIZE); 
    for (int i = 0; i < SIZE; i++) { 
        scanf("%d", &arr[i]); 
    } 
    FCFS(arr, head, SIZE); 
    return 0;
}