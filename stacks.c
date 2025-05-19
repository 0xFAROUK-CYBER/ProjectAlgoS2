// stacks.c
#include "stacks.h"

//----------BASIC STACKS FUNCTIONS-------*

void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

void push(Stack* stack, SLogEntry log) {
    if (isFull(stack)) {
        printf("Stack is full! Cannot push.\n");
        return;
    }
    stack->top++;
    stack->entries[stack->top] = log;
}

SLogEntry pop(Stack* stack) {
    SLogEntry emptyLog = {0, "", 0, ""};
    if (isEmpty(stack)) {
        printf("Stack is empty! Cannot pop.\n");
        return emptyLog;
    }
    return stack->entries[stack->top--];
}

SLogEntry peek(Stack* stack) {
    SLogEntry emptyLog = {0, "", 0, ""};
    if (isEmpty(stack)) {
        printf("Stack is empty! Nothing to peek.\n");
        return emptyLog;
    }
    return stack->entries[stack->top];
}

void insertAtBottom(Stack* stack, SLogEntry log) {
    if (isEmpty(stack)) {
        push(stack, log);
        return;
    }
    SLogEntry temp = pop(stack);
    insertAtBottom(stack, log);
    push(stack, temp);
}

void reverseStack(Stack* stack) {
    if (isEmpty(stack)) return;
    SLogEntry temp = pop(stack);
    reverseStack(stack);
    insertAtBottom(stack, temp);
}
