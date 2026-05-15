#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int Allocation[n][m], Request[n][m], Available[m];
    int Finish[n], Work[m];

    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &Request[i][j]);

    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &Available[i]);
        Work[i] = Available[i];
    }

    for(i = 0; i < n; i++)
        Finish[i] = 0;

    for(k = 0; k < n; k++) {
        for(i = 0; i < n; i++) {
            if(Finish[i] == 0) {
                int possible = 1;

                for(j = 0; j < m; j++) {
                    if(Request[i][j] > Work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {
                    for(j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];

                    Finish[i] = 1;
                }
            }
        }
    }

    int deadlock = 0;

    printf("\nProcesses in Deadlock:\n");

    for(i = 0; i < n; i++) {
        if(Finish[i] == 0) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0)
        printf("No Deadlock Detected");

    printf("\n");

    return 0;
}
