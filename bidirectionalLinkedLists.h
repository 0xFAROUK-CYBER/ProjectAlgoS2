// bidirectionalLinkedLists.h
#ifndef BIDIRECTIONALLINKEDLISTS_H
#define BIDIRECTIONALLINKEDLISTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DLogEntry {
    int id;
    char timestamp[20];
    int severity;
    char message[100];
    struct DLogEntry* next;
    struct DLogEntry* prev;
} DLogEntry;

// Function prototypes
DLogEntry* insertDLogAtEnd(DLogEntry* head, int id, const char* timestamp, int severity, const char* message);
DLogEntry* moveForward(DLogEntry* head, int steps);
DLogEntry* moveBackward(DLogEntry* tail, int steps);
DLogEntry* deleteMiddleNode(DLogEntry* head);
DLogEntry* mergeDLists(DLogEntry* list1, DLogEntry* list2);

#endif