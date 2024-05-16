#include <stdio.h>
#include <stdlib.h>

void SCAN(int *arr, int size, int head, char direction) { 
    int seek_count = 0; 
    int distance, cur_track; 
    int left[size], right[size]; 
    int left_size = 0, right_size = 0; 
    int *seek_sequence = (int *)malloc(2 * size * sizeof(int)); 
    if (seek_sequence == NULL) { 
        printf("Memory allocation failed.\n"); 
        exit(1); 
    } 
    if (direction == 'l') { 
        left[left_size++] = 0; 
    } 
    else if (direction == 'r') { 
        right[right_size++] = 199; 
    } 
    for (int i = 0; i < size; i++) { 
        if (arr[i] < head) { 
            left[left_size++] = arr[i]; 
        } 
        if (arr[i] > head) { 
            right[right_size++] = arr[i]; 
        } 
    } 
    for (int run = 0; run < 2; run++) { 
        if (direction == 'l') { 
            for (int i = left_size - 1; i >= 0; i--) { 
                cur_track = left[i]; 
                seek_sequence[seek_count++] = cur_track; 
                distance = abs(cur_track - head); 
                seek_count += distance; 
                head = cur_track; 
            } 
            direction = 'r'; 
        } 
        else if (direction == 'r') { 
            for (int i = 0; i < right_size; i++) { 
                cur_track = right[i]; 
                seek_sequence[seek_count++] = cur_track; 
                distance = abs(cur_track - head); 
                seek_count += distance; 
                head = cur_track; 
            } 
            direction = 'l';
        } 
    } 
    printf("Total number of seek operations = %d\n", seek_count); 
    free(seek_sequence);
}

int main() { 
    int head; 
    printf("Enter the initial position of the disk head: "); 
    scanf("%d", &head); 
    int size; 
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
    char direction; 
    printf("Enter the initial direction of disk movement ('l' for left, 'r' for right): "); 
    scanf(" %c", &direction); 
    SCAN(arr, size, head, direction); 
    free(arr); 
    return 0;
}