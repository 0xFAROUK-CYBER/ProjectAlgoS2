// circularLists.h
#ifndef CIRCULARLISTS_H
#define CIRCULARLISTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOGS 10 // Fixed size buffer for circular log buffer

typedef struct CLogEntry {
    int id;
    char timestamp[20];
    int severity;
    char message[100];
    struct CLogEntry* next;
} CLogEntry;

// Function Prototypes
CLogEntry* createCNode(int id, const char* timestamp, int severity, const char* message);
CLogEntry* insertCircular(CLogEntry* tail, int id, const char* timestamp, int severity, const char* message);
CLogEntry* insertAtPositionCircular(CLogEntry* tail, int position, int id, const char* timestamp, int severity, const char* message);
CLogEntry* deleteByIDCircular(CLogEntry* tail, int id);
CLogEntry* deleteFirstCircular(CLogEntry* tail);
CLogEntry* deleteLastCircular(CLogEntry* tail);
CLogEntry* searchByIDCircular(CLogEntry* tail, int id);
CLogEntry* searchByTimestampCircular(CLogEntry* tail, const char* timestamp);
CLogEntry* searchByKeywordCircular(CLogEntry* tail, const char* keyword);
CLogEntry* sortByDateCircular(CLogEntry* tail);
CLogEntry* sortBySeverityCircular(CLogEntry* tail);
CLogEntry* reverseCircular(CLogEntry* tail);
int countLogsCircular(CLogEntry* tail);

void traverseCircular(CLogEntry* tail);
CLogEntry* createFixedSizeBuffer(CLogEntry* tail, int id, const char* timestamp, int severity, const char* message, int* size);
int detectCycle(CLogEntry* head);

#endif