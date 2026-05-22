#include <stdio.h>
#include <stdbool.h>

int main() {
    int p, r;

    printf("Enter number of processes: ");
    scanf("%d", &p);

    printf("Enter number of resource types: ");
    scanf("%d", &r);

    int allocation[p][r];
    int request[p][r];
    int available[r];
    int work[r];
    bool finish[p];

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < p; i++) {
        printf("Process P%d: ", i);
        for(int j = 0; j < r; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(int i = 0; i < p; i++) {
        printf("Process P%d: ", i);
        for(int j = 0; j < r; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < r; i++) {
        printf("Resource R%d: ", i);
        scanf("%d", &available[i]);
    }

    // Initialize work = available
    for(int i = 0; i < r; i++) {
        work[i] = available[i];
    }

    // Initialize finish
    for(int i = 0; i < p; i++) {
        finish[i] = false;

        for(int j = 0; j < r; j++) {
            if(allocation[i][j] != 0) {
                finish[i] = false;
                break;
            }
        }
    }

    bool found;

    do {
        found = false;

        for(int i = 0; i < p; i++) {

            if(!finish[i]) {

                int j;

                for(j = 0; j < r; j++) {
                    if(request[i][j] > work[j]) {
                        break;
                    }
                }

                // Request can be satisfied
                if(j == r) {

                    for(int k = 0; k < r; k++) {
                        work[k] += allocation[i][k];
                    }

                    finish[i] = true;
                    found = true;
                }
            }
        }

    } while(found);

    bool deadlock = false;

    printf("\nDeadlock Detection Result:\n");

    for(int i = 0; i < p; i++) {

        if(!finish[i]) {
            printf("Process P%d is deadlocked.\n", i);
            deadlock = true;
        }
    }

    if(!deadlock) {
        printf("No deadlock detected.\n");
    }

    return 0;
}