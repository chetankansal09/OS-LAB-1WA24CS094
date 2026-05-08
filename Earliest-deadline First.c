#include <stdio.h>

struct Task {
    int exec, period, remain, deadline;
};

int main() {
    struct Task t[10];
    int n, time, sim;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Execution time and Period of Task %d: ", i + 1);
        scanf("%d %d", &t[i].exec, &t[i].period);

        t[i].remain = 0;
        t[i].deadline = t[i].period;
    }

    printf("Enter simulation time: ");
    scanf("%d", &sim);

    printf("\nEDF Schedule:\n");

    for(time = 0; time < sim; time++) {


        for(int i = 0; i < n; i++) {
            if(time % t[i].period == 0) {
                t[i].remain = t[i].exec;
                t[i].deadline = time + t[i].period;
            }
        }


        int early = -1;

        for(int i = 0; i < n; i++) {
            if(t[i].remain > 0) {
                if(early == -1 || t[i].deadline < t[early].deadline)
                    early = i;
            }
        }

        if(early != -1) {
            printf("T%d ", early + 1);
            t[early].remain--;
        } else {
            printf("Idle ");
        }
    }

    return 0;
}
