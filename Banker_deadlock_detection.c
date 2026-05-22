#include <stdio.h>
#include <stdbool.h>

int main() {
    int p, r;
    
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resource types: ");
    scanf("%d", &r);

    int allocation[p][r];
    int available[r];
    int work[r];
    bool finish[p];

    printf("\n--- Enter Available Resources ---\n");
    for(int i = 0; i < r; i++) {
        printf("Resource R%d: ", i);
        scanf("%d", &available[i]);
    }

    printf("\n--- Enter Current Allocation Matrix ---\n");
    for(int i = 0; i < p; i++) {
        printf("Process P%d: ", i);
        for(int j = 0; j < r; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    while(1) {
        printf("\n==================================\n");
        printf("      Deadlock Simulation Menu      \n");
        printf("==================================\n");
        printf("1. Banker's Algorithm (Avoidance)\n");
        printf("2. Deadlock Detection\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        
        int choice;
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                printf("\n--- Banker's Algorithm (Avoidance) ---\n");
                int max[p][r];
                int need[p][r];
                int safe_sequence[p];

                printf("Enter Maximum Requirement Matrix:\n");
                for(int i = 0; i < p; i++) {
                    printf("Process P%d: ", i);
                    for(int j = 0; j < r; j++) {
                        scanf("%d", &max[i][j]);
                        need[i][j] = max[i][j] - allocation[i][j];
                    }
                }

                for(int i = 0; i < r; i++) work[i] = available[i];
                for(int i = 0; i < p; i++) finish[i] = false;

                int count = 0;
                while(count < p) {
                    bool found = false;
                    for(int i = 0; i < p; i++) {
                        if(!finish[i]) {
                            int j;
                            for(j = 0; j < r; j++) {
                                if(need[i][j] > work[j]) break;
                            }
                            if(j == r) { 
                                for(int k = 0; k < r; k++) work[k] += allocation[i][k];
                                safe_sequence[count++] = i;
                                finish[i] = true;
                                found = true;
                            }
                        }
                    }
                    if(!found) {
                        printf("\n>> System is in an UNSAFE state. Deadlock possible.\n");
                        break;
                    }
                }

                if(count == p) {
                    printf("\n>> System is in a SAFE state.\n>> Safe Sequence: ");
                    for(int i = 0; i < p; i++) printf("P%d ", safe_sequence[i]);
                    printf("\n");
                }
                break;
            }
            
            case 2: {
                printf("\n--- Deadlock Detection Algorithm ---\n");
                int request[p][r];
                
                printf("Enter Current Request Matrix:\n");
                for(int i = 0; i < p; i++) {
                    printf("Process P%d: ", i);
                    for(int j = 0; j < r; j++) {
                        scanf("%d", &request[i][j]);
                    }
                }

                for(int i = 0; i < r; i++) work[i] = available[i];
                for(int i = 0; i < p; i++) {
                    finish[i] = true; 
                    for(int j = 0; j < r; j++) {
                        if(allocation[i][j] != 0) {
                            finish[i] = false;
                            break;
                        }
                    }
                }

               
                bool progress;
                do {
                    progress = false;
                    for(int i = 0; i < p; i++) {
                        if(!finish[i]) {
                            int j;
                            for(j = 0; j < r; j++) {
                                if(request[i][j] > work[j]) break;
                            }
                            if(j == r) { 
                                for(int k = 0; k < r; k++) work[k] += allocation[i][k];
                                finish[i] = true;
                                progress = true;
                            }
                        }
                    }
                } while(progress);

                bool is_deadlocked = false;
                printf("\n>> Result: ");
                for(int i = 0; i < p; i++) {
                    if(!finish[i]) {
                        if(!is_deadlocked) printf("System is DEADLOCKED.\n>> Processes involved: ");
                        printf("P%d ", i);
                        is_deadlocked = true;
                    }
                }
                if(!is_deadlocked) {
                    printf("System is NOT deadlocked.\n");
                } else {
                    printf("\n");
                }
                break;
            }
            
            case 3:
                printf("Exiting program...\n");
                return 0;
                
            default:
                printf("Invalid choice! Please enter 1, 2, or 3.\n");
        }
    }
    return 0;
}