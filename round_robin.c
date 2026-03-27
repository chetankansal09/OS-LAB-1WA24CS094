#include <stdio.h>

int main() {
    int n, i, time = 0, remain, quantum;
    int wt[10], tat[10], bt[10], rem_bt[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    remain = n;


    for(i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);


    while(remain != 0) {
        for(i = 0; i < n; i++) {
            if(rem_bt[i] > 0) {
                if(rem_bt[i] <= quantum) {
                    time += rem_bt[i];
                    rem_bt[i] = 0;
                    tat[i] = time;
                    wt[i] = tat[i] - bt[i];
                    remain--;
                } else {
                    rem_bt[i] -= quantum;
                    time += quantum;
                }
            }
        }
    }


    printf("\nProcess\tBurst Time\tTurnaround Time\tWaiting Time\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], tat[i], wt[i]);
    }

    float total_wt = 0, total_tat = 0;
    for(i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
