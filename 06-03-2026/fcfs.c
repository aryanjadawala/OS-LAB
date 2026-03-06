#include <stdio.h>

struct Process {
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    struct Process temp;

    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d:\n", p[i].id);
        printf("  Enter Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("  Enter Burst Time: ");
        scanf("%d", &p[i].bt);
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].at > p[j+1].at) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int current_time = 0;

    for(int i = 0; i < n; i++) {
        if(current_time < p[i].at) {
            current_time = p[i].at;
        }

        p[i].ct = current_time + p[i].bt;

        p[i].tat = p[i].ct - p[i].at;

        p[i].wt = p[i].tat - p[i].bt;

        current_time = p[i].ct;
    }

    float sum_wt = 0, sum_tat = 0;
    for(int i = 0; i < n; i++) {
        sum_wt += p[i].wt;
        sum_tat += p[i].tat;
    }

    float avg_wt = sum_wt / n;
    float avg_tat = sum_tat / n;

    printf("\n--------------------------------------------------------------------------------\n");
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    printf("--------------------------------------------------------------------------------\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("--------------------------------------------------------------------------------\n");
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time    = %.2f\n", avg_wt);

    return 0;
}
