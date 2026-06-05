#include <stdio.h>

void firstFit(int blocks[], int nb, int process[], int np) {
    int b[20];

    for(int i = 0; i < nb; i++)
        b[i] = blocks[i];

    printf("\n----- FIRST FIT -----\n");
    printf("Process\tSize\tBlock\n");

    for(int i = 0; i < np; i++) {
        int allocated = 0;

        for(int j = 0; j < nb; j++) {
            if(b[j] >= process[i]) {
                printf("P%d\t%d\t%d\n", i+1, process[i], j+1);
                b[j] -= process[i];
                allocated = 1;
                break;
            }
        }

        if(!allocated)
            printf("P%d\t%d\tNot Allocated\n", i+1, process[i]);
    }
}

void bestFit(int blocks[], int nb, int process[], int np) {
    int b[20];

    for(int i = 0; i < nb; i++)
        b[i] = blocks[i];

    printf("\n----- BEST FIT -----\n");
    printf("Process\tSize\tBlock\n");

    for(int i = 0; i < np; i++) {
        int best = -1;

        for(int j = 0; j < nb; j++) {
            if(b[j] >= process[i]) {
                if(best == -1 || b[j] < b[best])
                    best = j;
            }
        }

        if(best != -1) {
            printf("P%d\t%d\t%d\n", i+1, process[i], best+1);
            b[best] -= process[i];
        }
        else {
            printf("P%d\t%d\tNot Allocated\n", i+1, process[i]);
        }
    }
}

void worstFit(int blocks[], int nb, int process[], int np) {
    int b[20];

    for(int i = 0; i < nb; i++)
        b[i] = blocks[i];

    printf("\n----- WORST FIT -----\n");
    printf("Process\tSize\tBlock\n");

    for(int i = 0; i < np; i++) {
        int worst = -1;

        for(int j = 0; j < nb; j++) {
            if(b[j] >= process[i]) {
                if(worst == -1 || b[j] > b[worst])
                    worst = j;
            }
        }

        if(worst != -1) {
            printf("P%d\t%d\t%d\n", i+1, process[i], worst+1);
            b[worst] -= process[i];
        }
        else {
            printf("P%d\t%d\tNot Allocated\n", i+1, process[i]);
        }
    }
}

int main() {
    int nb, np;

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);

    int blocks[20];

    printf("Enter block sizes:\n");
    for(int i = 0; i < nb; i++)
        scanf("%d", &blocks[i]);

    printf("Enter number of processes: ");
    scanf("%d", &np);

    int process[20];

    printf("Enter process sizes:\n");
    for(int i = 0; i < np; i++)
        scanf("%d", &process[i]);

    firstFit(blocks, nb, process, np);
    bestFit(blocks, nb, process, np);
    worstFit(blocks, nb, process, np);

    return 0;
}
