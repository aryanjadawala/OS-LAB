#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m], finish[n], safeSeq[n];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Max Matrix
    printf("\nEnter Max Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate Need Matrix
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize Finish array
    for(i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int work[m];

    // Copy available to work
    for(i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;

    while(count < n) {

        int found = 0;

        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                // Check if Need <= Work
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                // If process can execute
                if(possible) {

                    // Release resources
                    for(j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }

                    safeSeq[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        // No process could be executed
        if(found == 0) {
            break;
        }
    }

    // Check Safe State
    if(count == n) {

        printf("\nSystem is in SAFE state.\n");

        printf("Safe Sequence: ");

        for(i = 0; i < n; i++) {
            printf("P%d", safeSeq[i]);

            if(i != n - 1) {
                printf(" -> ");
            }
        }

        printf("\n");
    }
    else {
        printf("\nSystem is NOT in SAFE state.\n");
    }

    return 0;
}
