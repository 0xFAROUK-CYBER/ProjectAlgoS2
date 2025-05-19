
// linkedLists.c
#include "linkedLists.h"

LogEntry* createNode(int id, const char* timestamp, int severity, const char* message) {
    LogEntry* newNode = (LogEntry*)malloc(sizeof(LogEntry));
    newNode->id = id;
    strcpy(newNode->timestamp, timestamp);
    newNode->severity = severity;
    strcpy(newNode->message, message);
    newNode->next = NULL;
    return newNode;
}

LogEntry* insertAtBeginning(LogEntry* head, int id, const char* timestamp, int severity, const char* message) {
    LogEntry* newNode = createNode(id, timestamp, severity, message);
    newNode->next = head;
    return newNode;
}

LogEntry* insertAtEnd(LogEntry* head, int id, const char* timestamp, int severity, const char* message) {
    LogEntry* newNode = createNode(id, timestamp, severity, message);
    if (!head) return newNode;
    LogEntry* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return head;
}

LogEntry* insertAtPosition(LogEntry* head, int position, int id, const char* timestamp, int severity, const char* message) {
    if (position <= 0) return insertAtBeginning(head, id, timestamp, severity, message);
    LogEntry* temp = head;
    for (int i = 0; i < position - 1 && temp; i++) temp = temp->next;
    if (!temp) return insertAtEnd(head, id, timestamp, severity, message);
    LogEntry* newNode = createNode(id, timestamp, severity, message);
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

LogEntry* deleteByID(LogEntry* head, int id) {
    if (!head) return NULL;
    if (head->id == id) {
        LogEntry* temp = head->next;
        free(head);
        return temp;
    }
    LogEntry* temp = head;
    while (temp->next && temp->next->id != id) temp = temp->next;
    if (temp->next) {
        LogEntry* toDelete = temp->next;
        temp->next = temp->next->next;
        free(toDelete);
    }
    return head;
}

LogEntry* deleteByTimestamp(LogEntry* head, const char* timestamp) {
    if (!head) return NULL;
    if (strcmp(head->timestamp, timestamp) == 0) {
        LogEntry* temp = head->next;
        free(head);
        return temp;
    }
    LogEntry* temp = head;
    while (temp->next && strcmp(temp->next->timestamp, timestamp) != 0) temp = temp->next;
    if (temp->next) {
        LogEntry* toDelete = temp->next;
        temp->next = temp->next->next;
        free(toDelete);
    }
    return head;
}

LogEntry* deleteFirst(LogEntry* head) {
    if (!head) return NULL;
    LogEntry* temp = head->next;
    free(head);
    return temp;
}

LogEntry* deleteLast(LogEntry* head) {
    if (!head || !head->next) {
        free(head);
        return NULL;
    }
    LogEntry* temp = head;
    while (temp->next->next) temp = temp->next;
    free(temp->next);
    temp->next = NULL;
    return head;
}

LogEntry* searchByID(LogEntry* head, int id) {
    while (head && head->id != id) head = head->next;
    return head;
}

LogEntry* searchByKeyword(LogEntry* head, const char* keyword) {
    while (head) {
        if (strstr(head->message, keyword)) return head;
        head = head->next;
    }
    return NULL;
}

LogEntry* searchByTimestamp(LogEntry* head, const char* timestamp) {
    while (head && strcmp(head->timestamp, timestamp) != 0) head = head->next;
    return head;
}

int compareTimestamps(const char* a, const char* b) {
    return strcmp(a, b); // Simple lexicographical comparison
}

LogEntry* sortByDate(LogEntry* head) {
    if (!head || !head->next) return head;
    for (LogEntry* i = head; i && i->next; i = i->next) {
        for (LogEntry* j = i->next; j; j = j->next) {
            if (compareTimestamps(i->timestamp, j->timestamp) > 0) {
                LogEntry temp = *i;
                *i = *j;
                *j = temp;
                LogEntry* t = i->next;
                i->next = j->next;
                j->next = t;
            }
        }
    }
    return head;
}

LogEntry* sortBySeverity(LogEntry* head) {
    if (!head || !head->next) return head;
    for (LogEntry* i = head; i && i->next; i = i->next) {
        for (LogEntry* j = i->next; j; j = j->next) {
            if (i->severity > j->severity) {
                LogEntry temp = *i;
                *i = *j;
                *j = temp;
                LogEntry* t = i->next;
                i->next = j->next;
                j->next = t;
            }
        }
    }
    return head;
}

LogEntry* reverseList(LogEntry* head) {
    LogEntry *prev = NULL, *curr = head, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int countLogs(LogEntry* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}
