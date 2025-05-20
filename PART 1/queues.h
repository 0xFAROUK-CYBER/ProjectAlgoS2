// queues.h
#ifndef QUEUES_H
#define QUEUES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100

typedef struct QLogEntry {
    int id;
    char timestamp[20];
    int severity;
    char message[100];
} QLogEntry;

typedef struct Queue {
    QLogEntry entries[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} Queue;

// Function Prototypes
void initQueue(Queue* q);
int isQueueEmpty(Queue* q);
int isQueueFull(Queue* q);
void enqueue(Queue* q, QLogEntry log);
QLogEntry dequeue(Queue* q);
QLogEntry peekQueue(Queue* q);

#endif