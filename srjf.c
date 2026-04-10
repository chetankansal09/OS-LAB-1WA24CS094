#include <stdio.h>
#include <limits.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rt;
    int remaining_bt;
    int started;
};

void sjf_non_preemptive(struct Process p[], int n) {
    int completed = 0, current_time = 0;
    int is_completed[n];

    for(int i = 0; i < n; i++) is_completed[i] = 0;

    printf("\n--- Non-Preemptive SJF ---\nGantt Chart:\n");

    while(completed != n) {
        int idx = -1;
        int min_bt = INT_MAX;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= current_time && !is_completed[i]) {
                if(p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            printf("| P%d ", p[idx].pid);

            current_time += p[idx].bt;

            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].wt;

            is_completed[idx] = 1;
            completed++;
        } else {
            current_time++;
        }
    }
    printf("|\n");

    float atat = 0, awt = 0, art = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++) {
        atat += p[i].tat;
        awt += p[i].wt;
        art += p[i].rt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage TAT = %.2f", atat/n);
    printf("\nAverage WT  = %.2f", awt/n);
    printf("\nAverage RT  = %.2f\n", art/n);
}

void sjf_preemptive(struct Process p[], int n) {
    int current_time = 0, completed = 0;
    int prev = -1;

    printf("\n--- Preemptive SJF (SRTF) ---\nGantt Chart:\n");

    while(completed != n) {
        int idx = -1;
        int min_bt = INT_MAX;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= current_time && p[i].remaining_bt > 0) {
                if(p[i].remaining_bt < min_bt) {
                    min_bt = p[i].remaining_bt;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            if(prev != idx) {
                printf("| P%d ", p[idx].pid);
                prev = idx;
            }

            if(p[idx].started == 0) {
                p[idx].rt = current_time - p[idx].at;
                p[idx].started = 1;
            }

            p[idx].remaining_bt--;
            current_time++;

            if(p[idx].remaining_bt == 0) {
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        } else {
            current_time++;
        }
    }
    printf("|\n");

    float atat = 0, awt = 0, art = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++) {
        atat += p[i].tat;
        awt += p[i].wt;
        art += p[i].rt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage TAT = %.2f", atat/n);
    printf("\nAverage WT  = %.2f", awt/n);
    printf("\nAverage RT  = %.2f\n", art/n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n], p_copy[n];

    for(int i = 0; i < n; i++) {
        printf("Enter PID, AT, BT for process %d: ", i+1);
        scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].bt);

        p[i].remaining_bt = p[i].bt;
        p[i].started = 0;

        p_copy[i] = p[i];
    }

    sjf_non_preemptive(p, n);
    sjf_preemptive(p_copy, n);

    return 0;
}
