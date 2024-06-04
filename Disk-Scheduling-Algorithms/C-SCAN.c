#include <stdio.h>
#include <stdlib.h>

void CSCAN(int arr[], int size, int head, int disk_size) { 
    int seek_count = 0; 
    int distance, cur_track; 
    int left[size], right[size]; 
    int left_size = 0, right_size = 0; 
    int *seek_sequence = (int *)malloc(2 * size * sizeof(int)); 
    if (seek_sequence == NULL) { 
        printf("Memory allocation failed.\n"); 
        exit(1); 
    } 
    left[left_size++] = 0; 
    right[right_size++] = disk_size - 1; 
    for (int i = 0; i < size; i++) { 
        if (arr[i] < head) { 
            left[left_size++] = arr[i]; 
        } 
        if (arr[i] > head) { 
            right[right_size++] = arr[i]; 
        } 
    } 
    for (int i = 0; i < right_size; i++) { 
        cur_track = right[i]; 
        seek_sequence[seek_count++] = cur_track; 
        distance = abs(cur_track - head); 
        seek_count += distance; 
        head = cur_track; 
    } 
    head = 0; 
    seek_count += (disk_size - 1); 
    for (int i = 0; i < left_size; i++) { 
        cur_track = left[i]; 
        seek_sequence[seek_count++] = cur_track; 
        distance = abs(cur_track - head); 
        seek_count += distance; 
        head = cur_track; 
    } 
    printf("Total number of seek operations = %d\n", seek_count); 
    free(seek_sequence);
}

int main() { 
    int head, disk_size, size; 
    printf("Enter the initial position of the disk head: "); 
    scanf("%d", &head); 
    printf("Enter the number of elements in the request array: "); 
    scanf("%d", &size); 
    int *arr = (int *)malloc(size * sizeof(int)); 

    if (arr == NULL) {
        printf("Memory allocation failed.\n"); 
        return 1; 
    } 
    printf("Enter the request array (%d elements):\n", size); 
    for (int i = 0; i < size; i++) { 
        scanf("%d", &arr[i]); 
    } 
    printf("Enter the disk size: "); 
    scanf("%d", &disk_size); 
    CSCAN(arr, size, head, disk_size); 
    free(arr); 
    return 0;
}