#include <stdio.h>

#define MAX 50

int main() {
    int nK, nS, nU;

    // Kernel arrays
    int atK[MAX], btK[MAX], ctK[MAX], wtK[MAX], tatK[MAX], doneK[MAX] = {0};

    // System arrays
    int atS[MAX], btS[MAX], ctS[MAX], wtS[MAX], tatS[MAX], doneS[MAX] = {0};

    // User arrays
    int atU[MAX], btU[MAX], ctU[MAX], wtU[MAX], tatU[MAX], doneU[MAX] = {0};

    int time = 0, completed = 0;

    // INPUT
    printf("Enter number of System processes: ");
    scanf("%d", &nK);
    for (int i = 0; i < nK; i++) {
        printf("S%d (AT BT): ", i+1);
        scanf("%d %d", &atK[i], &btK[i]);
    }

    printf("\nEnter number of Interactive processes: ");
    scanf("%d", &nS);
    for (int i = 0; i < nS; i++) {
        printf("I%d (AT BT): ", i+1);
        scanf("%d %d", &atS[i], &btS[i]);
    }

    printf("\nEnter number of Batch processes: ");
    scanf("%d", &nU);
    for (int i = 0; i < nU; i++) {
        printf("B%d (AT BT): ", i+1);
        scanf("%d %d", &atU[i], &btU[i]);
    }

    int total = nK + nS + nU;

    // SCHEDULING
    while (completed < total) {
        int idx = -1;

        // Kernel (Highest Priority)
        for (int i = 0; i < nK; i++) {
            if (!doneK[i] && atK[i] <= time) {
                if (idx == -1 || atK[i] < atK[idx])
                    idx = i;
            }
        }

        if (idx != -1) {
            time += btK[idx];
            ctK[idx] = time;
            tatK[idx] = ctK[idx] - atK[idx];
            wtK[idx] = tatK[idx] - btK[idx];
            doneK[idx] = 1;
            completed++;
            continue;
        }

        // System
        idx = -1;
        for (int i = 0; i < nS; i++) {
            if (!doneS[i] && atS[i] <= time) {
                if (idx == -1 || atS[i] < atS[idx])
                    idx = i;
            }
        }

        if (idx != -1) {
            time += btS[idx];
            ctS[idx] = time;
            tatS[idx] = ctS[idx] - atS[idx];
            wtS[idx] = tatS[idx] - btS[idx];
            doneS[idx] = 1;
            completed++;
            continue;
        }

        // User
        idx = -1;
        for (int i = 0; i < nU; i++) {
            if (!doneU[i] && atU[i] <= time) {
                if (idx == -1 || atU[i] < atU[idx])
                    idx = i;
            }
        }

        if (idx != -1) {
            time += btU[idx];
            ctU[idx] = time;
            tatU[idx] = ctU[idx] - atU[idx];
            wtU[idx] = tatU[idx] - btU[idx];
            doneU[idx] = 1;
            completed++;
            continue;
        }

        // CPU Idle
        time++;
    }

    // OUTPUT
    printf("\n--- System Processes ---\n");
    printf("PID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < nK; i++)
        printf("K%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, atK[i], btK[i], ctK[i], wtK[i], tatK[i]);

    printf("\n--- Interactive Processes ---\n");
    printf("PID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < nS; i++)
        printf("S%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, atS[i], btS[i], ctS[i], wtS[i], tatS[i]);

    printf("\n--- Batch Processes ---\n");
    printf("PID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < nU; i++)
        printf("U%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, atU[i], btU[i], ctU[i], wtU[i], tatU[i]);

    return 0;
}
