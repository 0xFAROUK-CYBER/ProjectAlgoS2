// recursion.h
#ifndef RECURSION_H
#define RECURSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct RLogEntry {
    int id;
    char timestamp[20];
    int severity;
    char message[100];
    struct RLogEntry* next;
} RLogEntry;

// Function Prototypes
RLogEntry* reverseListRecursive(RLogEntry* head);
int factorial(int n);
int fibonacci(int n);
int findMaxID(RLogEntry* head);
int binarySearchLog(RLogEntry* logs[], int left, int right, int targetID);
void infixToPostfix(const char* infix, char* postfix, int* index);

#endif