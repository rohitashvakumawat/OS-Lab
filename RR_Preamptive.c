#include <stdio.h>
#include <stdlib.h>

int main(){
    int p = 0;
    printf("Enter no. of processes: ");
    scanf("%d", &p);

    int btime[p];
    for(int i = 0 ; i<p;i++){
        printf("Enter Burst time for process %d: ", i+1);
        scanf("%d", &btime[i]);
    }

    int time = 0;
    printf("Enter time quantum in ms: ");
    scanf("%d",&time);

    int sum = 0;
    for(int k= 0;k<p;k++){
        sum += btime[k];
    }

    printf(" sum is %d", sum);

    int etime = 0;
    int entert = 0;

    while(sum!=0){
        for(int j = 0; j<p ; j++){
            if(btime[j] == 0);
            else if(btime[j] >= time){
                btime[j] -= time;
                etime += time;
                printf("\nProcess %d Entered at %d executed for %d ms | ETime %d | Remaining time for process left is %d: ", j+1,entert, time, etime ,btime[j]);
                sum -= time;
                entert +=time;
            }
            else{
                sum -=btime[j];
                etime += btime[j];
                printf("\nProcess %d Finished! Entered at %d executed for %d ms | Etime %d | Remaining time is %d ",j+1,entert,btime[j],etime,sum);
                btime[j] = 0;
                entert +=btime[j];
            }
        }

    }
    return 0;
}