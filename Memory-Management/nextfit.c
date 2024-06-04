#include <stdio.h>

void nextFit(int blockSize[],int m,int processSize[],int n)
{
    //Block allocations for process
    int allocation[n];

    //Initially allocate the index of -1 to all allocation blocks
    for (int i=0;i<n;i++)
    {
        allocation[i]=-1;
    }

    //Pointer to keep track of where last allocation was made
    int j=0;
    //Counter to keep track of how many blocks have been visited

    //Fetching the process and allocating block
    for (int i = 0; i < n; i++) { 
  
        int count=0;
        // Do not start from beginning 
        while (count < m) 
        { 
            if (blockSize[j] >= processSize[i]) { 
  
                // allocate block j to p[i] process 
                allocation[i] = j; 
  
                // Reduce available memory in this block. 
                blockSize[j] -= processSize[i]; 
  
                break; 
            } 
  
            // mod m will help in traversing the blocks from 
            // starting block after we reach the end.  
            j = (j + 1) % m; 
            count+=1;
        } 
    } 
    
    //Now printing the allocation array
    for(int i=0;i<n;i++)
    {
        if (allocation[i]!=-1)
            printf("\nBlock for Process No %d with Size %d is %d",i+1,processSize[i],allocation[i]+1);
        else
            printf("\nBlock for Process No %d with Size %d cannot be allocated",i+1,processSize[i]);
    }
    printf("\n\nEnd of process\n");
}


int main() 
{ 
    int blockSize[] = {100, 500, 200, 300, 600}; 
    int processSize[] = {212, 417, 112, 426}; 
    int m = sizeof(blockSize)/sizeof(blockSize[0]); 
    int n = sizeof(processSize)/sizeof(processSize[0]); 
  
    nextFit(blockSize, m, processSize, n); 
  
    return 0 ; 
} 