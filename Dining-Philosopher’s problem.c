

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forkS[N];

void *philosopher(void *num)
{
    int id = *(int *)num;

    while (1)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        sem_wait(&forkS[id]);
        sem_wait(&forkS[(id + 1) % N]);

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        sem_post(&forkS[id]);
        sem_post(&forkS[(id + 1) % N]);
    }
}

int main()
{
    pthread_t p[N];
    int id[N];

    for (int i = 0; i < N; i++)
        sem_init(&forkS[i], 0, 1);

    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(p[i], NULL);

    return 0;
}
