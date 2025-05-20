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

// Function Prototypes
DLogEntry* createDNode(int id, const char* timestamp, int severity, const char* message);
DLogEntry* insertAtBeginningD(DLogEntry* head, int id, const char* timestamp, int severity, const char* message);
DLogEntry* insertAtEndD(DLogEntry* head, int id, const char* timestamp, int severity, const char* message);
DLogEntry* insertAtPositionD(DLogEntry* head, int position, int id, const char* timestamp, int severity, const char* message);

DLogEntry* deleteByIDD(DLogEntry* head, int id);
DLogEntry* deleteFirstD(DLogEntry* head);
DLogEntry* deleteLastD(DLogEntry* head);
DLogEntry* deleteMiddleNode(DLogEntry* head);

DLogEntry* searchByIDD(DLogEntry* head, int id);
DLogEntry* searchByTimestampD(DLogEntry* head, const char* timestamp);
DLogEntry* searchByKeywordD(DLogEntry* head, const char* keyword);

DLogEntry* sortByDateD(DLogEntry* head);
DLogEntry* sortBySeverityD(DLogEntry* head);

DLogEntry* reverseListD(DLogEntry* head);
int countLogsD(DLogEntry* head);

DLogEntry* moveForward(DLogEntry* node, int steps);
DLogEntry* moveBackward(DLogEntry* node, int steps);
DLogEntry* mergeDLists(DLogEntry* list1, DLogEntry* list2);

#endif