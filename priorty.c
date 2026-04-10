#include <stdio.h>

struct P {
    int id, at, bt, pr, ct, tat, wt, done;
};

int main() {
    int n, completed = 0, time = 0;
    float atat = 0, awt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct P p[n];

    // Input
    for (int i = 0; i < n; i++) {
        printf("\nP%d AT BT Priority: ", i + 1);
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].id = i + 1;
        p[i].done = 0;
    }

    printf("\nGantt Chart:\n|");

    // Scheduling
    while (completed < n) {
        int idx = -1, min_pr = 999;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].pr < min_pr) {
                    min_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++; // idle time
        } else {
            printf(" P%d |", p[idx].id);

            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = 1;

            atat += p[idx].tat;
            awt += p[idx].wt;
            completed++;
        }
    }

    // Time line
    time = 0;
    printf("\n0");
    for (int i = 0; i < n; i++) {
        int min_ct = 9999, idx = -1;
        for (int j = 0; j < n; j++) {
            if (p[j].ct < min_ct && p[j].ct > time) {
                min_ct = p[j].ct;
                idx = j;
            }
        }
        if (idx != -1) {
            printf("   %d", p[idx].ct);
            time = p[idx].ct;
        }
    }

    // Table
    printf("\n\nPID AT BT PR CT TAT WT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d  %d  %d  %d  %d  %d  %d\n",
               p[i].id, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", atat / n);
    printf("\nAverage WT  = %.2f", awt / n);

    return 0;
}
