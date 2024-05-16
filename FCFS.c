#include <stdio.h>
#include <stdlib.h>


int main(){
    int p;
    printf("Enter no. of processes: ");
    scanf("%d ",&p);
    
    int btime[p];
    for(int i = 0 ; i<p;i++){
        printf("Enter Burst time for process %d: ", i+1);
        scanf("%d", &btime[i]);
    }

    
    int awt= 0;
    int wt = 0;
    int wtime[p];
    for(int i = 0; i<p-1; i++){
        wtime[i] = wt;
        wt += btime[i];
        awt += awt + btime[i];
    }
    wtime[p-1] = wt;

    for(int i=0; i<p;i++){
        printf("\nProcess %d Done with Burst time %d | waiting time %d | Turn around time %d ", i+1, btime[i], wtime[i],btime[i]+wtime[i]);
    }

    printf("\nAverage waiting time is: %d ms", awt/p);

    return 0;
}
