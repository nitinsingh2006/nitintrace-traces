// ══════════════════════════════════════════════════════
//  🧪 NitinTrace — AI Execution Trace
//
//  Language : c
//  Steps    : 25
//  Saved    : 24 Jun 2026, 3:52 pm
//  Tool     : NitinTrace (AI-Powered Code Visualizer)
// ══════════════════════════════════════════════════════
//
//  EXECUTION SUMMARY:
//  Step 1: The program starts execution from the first line, which includes the nec
//  Step 2: The program defines a constant N with a value of 5, representing the num
//  Step 3: An array of mutexes, forks, is declared with a size of N.
//  Step 4: The think function is defined, which makes a philosopher think for 1 sec
//  Step 5: The eat function is defined, which makes a philosopher eat for 1 second.
//  … and 20 more steps
//
// ══════════════════════════════════════════════════════

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // Number of philosophers

pthread_mutex_t forks[N];

void think(int id) {
    printf("Philosopher %d is thinking\n", id);
    sleep(1);
}

void eat(int id) {
    printf("Philosopher %d is eating\n", id);
    sleep(1);
}

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        think(id);

        if (id == N - 1) {
            // Last philosopher picks right fork first
            pthread_mutex_lock(&forks[right]);
            printf("Philosopher %d picked up fork %d\n", id, right);

            pthread_mutex_lock(&forks[left]);
            printf("Philosopher %d picked up fork %d\n", id, left);
        } else {
            pthread_mutex_lock(&forks[left]);
            printf("Philosopher %d picked up fork %d\n", id, left);

            pthread_mutex_lock(&forks[right]);
            printf("Philosopher %d picked up fork %d\n", id, right);
        }

        eat(id);

        pthread_mutex_unlock(&forks[left]);
        printf("Philosopher %d put down fork %d\n", id, left);

        pthread_mutex_unlock(&forks[right]);
        printf("Philosopher %d put down fork %d\n", id, right);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}