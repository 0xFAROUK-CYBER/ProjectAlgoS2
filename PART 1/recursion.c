// recursion.c
#include "recursion.h"


// 1) FUNCTION TO REVERSE A LIST RECURSIVELY
RLogEntry* reverseListRecursive(RLogEntry* head) {
    if (!head || !head->next) return head;
    RLogEntry* rest = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = NULL;
    return rest;
}

// 2) FUNCTION TH CALCULATE FACTORIAL OF N RECURSIVELY 
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// 3) FUNCTION TO CALCULATE THE FIBONACCI SEQUENCE RECURSIVELY:

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 4) FUNCTION TO FIND THE MAX ID
int findMaxID(RLogEntry* head) {
    if (!head) return -1;
    if (!head->next) return head->id;
    int maxRest = findMaxID(head->next);
    return (head->id > maxRest) ? head->id : maxRest;
}

 // 5) FUNCTION TO PREFORM BINARY SEARCH RECURSIVELY:

int binarySearchLog(RLogEntry* logs[], int left, int right, int targetID) {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (logs[mid]->id == targetID) return mid;
    else if (logs[mid]->id < targetID)
        return binarySearchLog(logs, mid + 1, right, targetID);
    else
        return binarySearchLog(logs, left, mid - 1, targetID);
}

 // 6) PROCEDURE  TO TRANSFORM INFIX INTO POSTFIX:

void infixToPostfix(const char* infix, char* postfix, int* index) {
    if (*infix == '\0') return;
    if (*infix >= '0' && *infix <= '9') {
        postfix[(*index)++] = *infix;
    } else if (*infix == '+' || *infix == '-' || *infix == '*' || *infix == '/') {
        infixToPostfix(infix + 1, postfix, index);
        postfix[(*index)++] = *infix;
    } else {
        infixToPostfix(infix + 1, postfix, index);
    }
    postfix[*index] = '\0';
}
