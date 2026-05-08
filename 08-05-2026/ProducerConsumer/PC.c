#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 8

int buffer[N];
int in = 0, out = 0;


sem_t empty;
sem_t full;
pthread_mutex_t S;


int produce_item() {
    static int item = 1;
    return item++;
}


void consume_item(int item) {
    printf("Consumed: %d\n", item);
}


void* producer(void* arg) {
    int itemP;

    while (1) {
        itemP = produce_item();

        sem_wait(&empty);
        pthread_mutex_lock(&S);

        buffer[in] = itemP;
        printf("Produced: %d at position %d\n", itemP, in);

        in = (in + 1) % N;

        pthread_mutex_unlock(&S);
        sem_post(&full);

        sleep(1);
    }

    return NULL;
}


void* consumer(void* arg) {
    int itemC;

    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&S);

        itemC = buffer[out];
        printf("Consumed: %d from position %d\n", itemC, out);

        out = (out + 1) % N;

        pthread_mutex_unlock(&S);
        sem_post(&empty);

        consume_item(itemC);

        sleep(2);
    }

    return NULL;
}

int main() {
    pthread_t prod, cons;


    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);


    pthread_mutex_init(&S, NULL);


    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);


    pthread_join(prod, NULL);
    pthread_join(cons, NULL);


    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&S);

    return 0;
}
