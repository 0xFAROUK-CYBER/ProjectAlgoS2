// stacks.h
#ifndef STACKS_H
#define STACKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef struct SLogEntry {
    int id;
    char timestamp[20];
    int severity;
    char message[100];
} SLogEntry;

typedef struct Stack {
    SLogEntry entries[MAX_STACK_SIZE];
    int top;
} Stack;

// Function Prototypes
void initStack(Stack* stack);
int isEmpty(Stack* stack);
int isFull(Stack* stack);
void push(Stack* stack, SLogEntry log);
SLogEntry pop(Stack* stack);
SLogEntry peek(Stack* stack);
void reverseStack(Stack* stack);
void insertAtBottom(Stack* stack, SLogEntry log);

#endif