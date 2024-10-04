#include <stdio.h>

#define PROCESS struct Process

PROCESS {
    int id;         // Process ID
    int bt;         // Burst Time
    int art;        // Arrival Time
    int remaining;  // Remaining Time
};

// Function to find the process with the smallest remaining time
int findShortestRemainingTime(PROCESS processes[], int n, int currentTime) {
    int minIndex = -1;
    int minRemainingTime = 9999; // A large number

    for (int i = 0; i < n; i++) {
        if (processes[i].art <= currentTime && processes[i].remaining < minRemainingTime && processes[i].remaining > 0) {
            minRemainingTime = processes[i].remaining;
            minIndex = i;
        }
    }

    return minIndex;
}

// Function to implement SRTF Scheduling
void srtfScheduling(PROCESS processes[], int n) {
    int completed = 0;
    int currentTime = 0;
    float totalWaitingTime = 0;
    float totalTurnAroundTime = 0;

    // Initialize remaining time
    for (int i = 0; i < n; i++) {
        processes[i].remaining = processes[i].bt;
    }

    while (completed < n) {
        int index = findShortestRemainingTime(processes, n, currentTime);

        if (index != -1) {
            processes[index].remaining--;
            currentTime++;

            if (processes[index].remaining == 0) {
                completed++;
                int turnAroundTime = currentTime - processes[index].art;
                int waitingTime = turnAroundTime - processes[index].bt;

                totalTurnAroundTime += turnAroundTime;
                totalWaitingTime += waitingTime;

                printf("Process %d finished at time %d\n", processes[index].id, currentTime);
            }
        } else {
            currentTime++;
        }
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    PROCESS processes[n];

    // Input for processes
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time and arrival time for process %d: ", processes[i].id);
        scanf("%d %d", &processes[i].bt, &processes[i].art);
    }

    srtfScheduling(processes, n);

    return 0;
}
