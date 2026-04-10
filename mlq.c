#include <stdio.h>

struct P {
    int id, at, bt, ct, tat, wt;
};

void fcfs(struct P p[], int n, int start) {
    int time = start;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

int main() {
    int n, sc = 0, uc = 0;
    float atat = 0, awt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct P sys[n], user[n], t;

    for (int i = 0; i < n; i++) {
        int type;
        printf("\nP%d AT BT Type(1=Sys,2=User): ", i + 1);
        scanf("%d%d%d", &t.at, &t.bt, &type);
        t.id = i + 1;

        if (type == 1)
            sys[sc++] = t;
        else
            user[uc++] = t;
    }

    // System first
    fcfs(sys, sc, 0);
    int last = (sc > 0) ? sys[sc - 1].ct : 0;

    // User next
    fcfs(user, uc, last);

    // Display table
    printf("\nPID AT BT CT TAT WT\n");

    for (int i = 0; i < sc; i++) {
        printf("P%d  %d  %d  %d  %d  %d\n",
               sys[i].id, sys[i].at, sys[i].bt,
               sys[i].ct, sys[i].tat, sys[i].wt);
        atat += sys[i].tat;
        awt += sys[i].wt;
    }

    for (int i = 0; i < uc; i++) {
        printf("P%d  %d  %d  %d  %d  %d\n",
               user[i].id, user[i].at, user[i].bt,
               user[i].ct, user[i].tat, user[i].wt);
        atat += user[i].tat;
        awt += user[i].wt;
    }

    // Averages
    atat /= n;
    awt /= n;

    printf("\nAverage TAT = %.2f", atat);
    printf("\nAverage WT  = %.2f\n", awt);

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < sc; i++)
        printf(" P%d |", sys[i].id);
    for (int i = 0; i < uc; i++)
        printf(" P%d |", user[i].id);

    printf("\n0");
    for (int i = 0; i < sc; i++)
        printf("   %d", sys[i].ct);
    for (int i = 0; i < uc; i++)
        printf("   %d", user[i].ct);

    return 0;
}
