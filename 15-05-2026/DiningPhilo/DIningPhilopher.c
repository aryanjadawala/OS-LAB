#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5 // Number of philosophers

sem_t forks[N];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left_fork = id;
    int right_fork = (id + 1) % N;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        if (id == N - 1) {
            // Philosopher 4 picks up Right then Left
            sem_wait(&forks[right_fork]);
            printf("Philosopher %d picked up right fork %d\n", id, right_fork);

            sem_wait(&forks[left_fork]);
            printf("Philosopher %d picked up left fork %d\n", id, left_fork);
        } else {
            // Others pick up Left then Right
            sem_wait(&forks[left_fork]);
            printf("Philosopher %d picked up left fork %d\n", id, left_fork);

            sem_wait(&forks[right_fork]);
            printf("Philosopher %d picked up right fork %d\n", id, right_fork);
        }

        printf("--- Philosopher %d is EATING ---\n", id);
        sleep(2);

        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);

        printf("Philosopher %d finished eating and dropped forks %d & %d.\n", id, left_fork, right_fork);
    }
}

int main() {
    pthread_t thread_id[N];
    int phil_ids[N];

    // Initialize semaphores for forks
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
        phil_ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil_ids[i]);
    }

    // Join threads (in this case, it runs forever)
    for (int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    // Cleanup
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
