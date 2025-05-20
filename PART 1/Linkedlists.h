// linkedLists.h
#ifndef LINKEDLISTS_H
#define LINKEDLISTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LogEntry {
    int id;
    char timestamp[20]; // Format: DD-MM-YYYY HH:MM:SS
    int severity;
    char message[100];
    struct LogEntry *next;
} LogEntry;

// Function Prototypes
LogEntry* insertAtBeginning(LogEntry* head, int id, const char* timestamp, int severity, const char* message);
LogEntry* insertAtEnd(LogEntry* head, int id, const char* timestamp, int severity, const char* message);
LogEntry* insertAtPosition(LogEntry* head, int position, int id, const char* timestamp, int severity, const char* message);

LogEntry* deleteByID(LogEntry* head, int id);
LogEntry* deleteByTimestamp(LogEntry* head, const char* timestamp);
LogEntry* deleteFirst(LogEntry* head);
LogEntry* deleteLast(LogEntry* head);

LogEntry* searchByID(LogEntry* head, int id);
LogEntry* searchByKeyword(LogEntry* head, const char* keyword);
LogEntry* searchByTimestamp(LogEntry* head, const char* timestamp);

LogEntry* sortByDate(LogEntry* head);
LogEntry* sortBySeverity(LogEntry* head);

LogEntry* reverseList(LogEntry* head);
int countLogs(LogEntry* head);

#endif
