// queues.c
#include "queues.h"

//   *----------QUEUES BASIC FUNCTIONS---------*

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isQueueEmpty(Queue* q) {
    return q->size == 0;
}

int isQueueFull(Queue* q) {
    return q->size == MAX_QUEUE_SIZE;
}

void enqueue(Queue* q, QLogEntry log) {
    if (isQueueFull(q)) {
        printf("Queue is full! Cannot enqueue.\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->entries[q->rear] = log;
    q->size++;
}

QLogEntry dequeue(Queue* q) {
    QLogEntry emptyLog = {0, "", 0, ""};
    if (isQueueEmpty(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return emptyLog;
    }
    QLogEntry log = q->entries[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->size--;
    return log;
}

QLogEntry peekQueue(Queue* q) {
    QLogEntry emptyLog = {0, "", 0, ""};
    if (isQueueEmpty(q)) {
        printf("Queue is empty! Nothing to peek.\n");
        return emptyLog;
    }
    return q->entries[q->front];
}
