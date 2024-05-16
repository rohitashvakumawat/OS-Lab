#include <stdio.h>
#include <limits.h>

struct Process {
    int id;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int arrivalTime;
    int remainingTime;
    int responseTime;
};

int isAllDone(struct Process processes[], int n) {
    for (int i = 0; i < n; ++i) {
        if (processes[i].remainingTime > 0) {
            return 0; // Some processes are still pending
        }
    }
    return 1; // All processes are done
}

void calculateTimesPreemptive(struct Process processes[], int n) {
    int currentTime = 0;

    while (!isAllDone(processes, n)) {
        int minBurstTime = INT_MAX;
        int selectedProcess = -1;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].burstTime < minBurstTime) {
                    minBurstTime = processes[i].burstTime;
                    selectedProcess = i;
                }
            }
        }

        if (selectedProcess == -1) {
        currentTime++;
        } else {
            if (processes[selectedProcess].responseTime == -1) {
                processes[selectedProcess].responseTime = currentTime;
            }

            processes[selectedProcess].remainingTime--;
            currentTime++;

            if (processes[selectedProcess].remainingTime == 0) {
                processes[selectedProcess].turnaroundTime = currentTime - processes[selectedProcess].arrivalTime;
                processes[selectedProcess].waitingTime = processes[selectedProcess].turnaroundTime -
                processes[selectedProcess].burstTime;
            }
        }
    }
}

void displayResults(struct Process processes[], int n) {
    float avgWaitingTime = 0, avgTurnaroundTime = 0, avgResponseTime = 0;

    printf("\nProcess Arrival Time Burst Time Waiting Time Turnaround Time Response Time\n");
    for (int i = 0; i < n; ++i) {
        printf("  %d  %d %d %d %d  %d\n",
        processes[i].id, processes[i].arrivalTime, processes[i].burstTime,
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

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].responseTime = -1; // -1 indicates response time not yet set
    }

    calculateTimesPreemptive(processes, n);
    displayResults(processes, n);

    return 0;
}