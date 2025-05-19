// trees.h
#ifndef TREES_H
#define TREES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TLogEntry {
    int id;
    char timestamp[20];
    int severity;
    char message[100];
    struct TLogEntry* left;
    struct TLogEntry* right;
} TLogEntry;

// BST Functions
TLogEntry* insertBST(TLogEntry* root, int id, const char* timestamp, int severity, const char* message);
TLogEntry* deleteBST(TLogEntry* root, const char* timestamp);
TLogEntry* searchBST(TLogEntry* root, const char* timestamp);
void inOrderTraversal(TLogEntry* root);
void preOrderTraversal(TLogEntry* root);
void postOrderTraversal(TLogEntry* root);

// Conversion
TLogEntry* sortedListToBST(TLogEntry** headRef, int n);
int countListNodes(TLogEntry* head);

// Heap Functions
void heapify(TLogEntry arr[], int n, int i);
void buildHeap(TLogEntry arr[], int n);

#endif