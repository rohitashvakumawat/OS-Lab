#include <stdio.h>

struct Process {
    int id;
    int burstTime;
    int priority;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;
};

void calculateTimes(struct Process processes[], int n) {
    processes[0].waitingTime = 0;
    processes[0].turnaroundTime = processes[0].burstTime;
    processes[0].responseTime = 0;

    for (int i = 1; i < n; ++i) {
        processes[i].waitingTime = processes[i - 1].turnaroundTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        processes[i].responseTime = processes[i].waitingTime;
    }
}

void displayResults(struct Process processes[], int n) {
    float avgWaitingTime = 0, avgTurnaroundTime = 0, avgResponseTime = 0;

    printf("\nProcess Arrival Time Burst Time Priority Waiting Time Turnaround Time Response Time\n");
    for (int i = 0; i < n; ++i) {
        printf("  %d      %d      %d       %d       %d          %d           %d\n",
                processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].priority,
                processes[i].waitingTime, processes[i].turnaroundTime, processes[i].responseTime);

        avgWaitingTime += processes[i].waitingTime;
        avgTurnaroundTime += processes[i].turnaroundTime;
        avgResponseTime += processes[i].responseTime;
    }

    avgWaitingTime /= n;
    avgTurnaroundTime /= n;
    avgResponseTime /= n;

    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
    printf("\nAverage Turnaround Time: %.2f", avgTurnaroundTime);
    printf("\nAverage Response Time: %.2f\n", avgResponseTime);
}

void sortProcesses(struct Process processes[], int n) {
    struct Process temp;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
    }

    sortProcesses(processes, n);
    calculateTimes(processes, n);
    displayResults(processes, n);

    return 0;
}
