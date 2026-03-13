#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id;
    int at; // Arrival Time
    int bt; // Burst Time
    int rt; // Remaining Time (for SRTF)
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
    bool is_completed; // for SJF
};

// Function to print the final table and averages
void printResults(struct Process p[], int n) {
    float sum_wt = 0, sum_tat = 0;
    printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        sum_wt += p[i].wt;
        sum_tat += p[i].tat;
    }
    printf("\nAverage Waiting Time: %.2f", sum_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n\n", sum_tat / n);
}

// 1. Non-Preemptive SJF Algorithm
void sjfNonPreemptive(struct Process p[], int n) {
    int completed = 0, current_time = 0;

    // Initialize tracking variables for a fresh run
    for (int i = 0; i < n; i++) {
        p[i].is_completed = false;
    }

    printf("\n--- Non-Preemptive SJF Execution ---\n");

    while (completed < n) {
        int idx = -1;
        int min_bt = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !p[i].is_completed) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                } else if (p[i].bt == min_bt) {
                    if (idx == -1 || p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            p[idx].ct = current_time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].is_completed = true;
            current_time = p[idx].ct;
            completed++;
        } else {
            current_time++;
        }
    }
    printResults(p, n);
}

// 2. Preemptive SJF (SRTF) Algorithm
void srtfPreemptive(struct Process p[], int n) {
    int completed = 0, current_time = 0;

    // Initialize remaining time for a fresh run
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
    }

    printf("\n--- Preemptive SJF (SRTF) Execution ---\n");

    while (completed < n) {
        int idx = -1;
        int min_rt = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                if (p[i].rt < min_rt) {
                    min_rt = p[i].rt;
                    idx = i;
                } else if (p[i].rt == min_rt) {
                    if (idx == -1 || p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            p[idx].rt--;
            current_time++;

            if (p[idx].rt == 0) {
                completed++;
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
            }
        } else {
            current_time++;
        }
    }
    printResults(p, n);
}

int main() {
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    do {
        printf("==================================\n");
        printf("       CPU SCHEDULING MENU        \n");
        printf("==================================\n");
        printf("1. Improved SJF (Non-Preemptive)\n");
        printf("2. Shortest Remaining Time First (Preemptive)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sjfNonPreemptive(p, n);
                break;
            case 2:
                srtfPreemptive(p, n);
                break;
            case 3:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please select 1, 2, or 3.\n\n");
        }
    } while (choice != 3);

    return 0;
}
