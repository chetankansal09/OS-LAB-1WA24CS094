#include <stdio.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int execution;
    int period;
    int remaining;
    int next_release;
} Task;

int main() {
    Task tasks[MAX_TASKS];
    int n, sim_time;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        tasks[i].id = i + 1;

        printf("\nTask %d\n", i + 1);

        printf("Execution Time: ");
        scanf("%d", &tasks[i].execution);

        printf("Period: ");
        scanf("%d", &tasks[i].period);

        tasks[i].remaining = 0;
        tasks[i].next_release = 0;
    }

    printf("\nEnter simulation time: ");
    scanf("%d", &sim_time);

    printf("\n===== Rate Monotonic Scheduling =====\n");

    for(int time = 0; time < sim_time; time++) {


        for(int i = 0; i < n; i++) {
            if(time == tasks[i].next_release) {
                tasks[i].remaining = tasks[i].execution;
                tasks[i].next_release += tasks[i].period;
            }
        }

        int selected = -1;

        for(int i = 0; i < n; i++) {
            if(tasks[i].remaining > 0) {
                if(selected == -1 ||
                   tasks[i].period < tasks[selected].period) {
                    selected = i;
                }
            }
        }


        if(selected != -1) {
            printf("Time %2d -> %2d : Task %d\n",
                   time, time + 1,
                   tasks[selected].id);

            tasks[selected].remaining--;
        }
        else {
            printf("Time %2d -> %2d : IDLE\n",
                   time, time + 1);
        }
    }

    return 0;
}
