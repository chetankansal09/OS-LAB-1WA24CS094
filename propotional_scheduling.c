#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_TASKS 5

typedef struct {
    int id;
    int burst_time;
    int remaining_time;
    int tickets;
} Process;

int main() {
    Process procs[MAX_TASKS];
    int n, total_tickets = 0;
    int current_time = 0;

    // Initialize random seed
    srand((unsigned)time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        procs[i].id = i + 1;
        printf("Process %d - Enter Burst Time and Tickets: ", i + 1);
        scanf("%d %d", &procs[i].burst_time, &procs[i].tickets);
        procs[i].remaining_time = procs[i].burst_time;
        total_tickets += procs[i].tickets;
    }

    printf("\n--- Starting Lottery Scheduling (Quantum = 1 unit) ---\n");

    while (total_tickets > 0) {
    
        int winning_ticket = (rand() % total_tickets) + 1;
        int ticket_sum = 0;
        int winner = -1;

        for (int i = 0; i < n; i++) {
            if (procs[i].remaining_time > 0) {
                ticket_sum += procs[i].tickets;
                if (ticket_sum >= winning_ticket) {
                    winner = i;
                    break;
                }
            }
        }

         if (winner != -1) {
             printf("Time [%d-%d] \t| Process %d runs (Ticket drawn: %d)\n", 
                 current_time, current_time + 1, procs[winner].id, winning_ticket);

             procs[winner].remaining_time--;
             current_time++;
            if (procs[winner].remaining_time == 0) {
                printf("          \t| -> Process %d finished!\n", procs[winner].id);
                total_tickets -= procs[winner].tickets;
            }
        }
    }

    printf("All processes have finished execution.\n");
    return 0;
}