#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int id;
    int burstTime;
    int remainingTime;
    int turnaroundTime;
    int waitingTime;
};

void roundRobin(struct Process processes[], int numProcesses, int timeQuantum) {
    int currentTime = 0;
    int remainingProcesses = numProcesses;

    while (remainingProcesses > 0) {
        for (int i = 0; i < numProcesses; ++i) {
            if (processes[i].remainingTime > 0) {
                int executionTime = (processes[i].remainingTime < timeQuantum) ? processes[i].remainingTime : timeQuantum;

                processes[i].remainingTime -= executionTime;
                currentTime += executionTime;

                if (processes[i].remainingTime == 0) {
                    processes[i].turnaroundTime = currentTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                    remainingProcesses--;
                }
            }
        }
    }
}

void displayResults(struct Process processes[], int numProcesses) {
    float avgWaitingTime = 0, avgTurnaroundTime = 0;

    printf("\nProcess Burst Time Waiting Time Turnaround Time\n");
    for (int i = 0; i < numProcesses; ++i) {
        printf("  %d      %d      %d          %d\n",
                processes[i].id, processes[i].burstTime,
                processes[i].waitingTime, processes[i].turnaroundTime);

        avgWaitingTime += processes[i].waitingTime;
        avgTurnaroundTime += processes[i].turnaroundTime;
    }

    avgWaitingTime /= numProcesses;
    avgTurnaroundTime /= numProcesses;

    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main() {
    int numProcesses, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[MAX_PROCESSES];

    for (int i = 0; i < numProcesses; ++i) {
        processes[i].id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].turnaroundTime = 0;
        processes[i].waitingTime = 0;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    roundRobin(processes, numProcesses, timeQuantum);
    displayResults(processes, numProcesses);

    return 0;
}
