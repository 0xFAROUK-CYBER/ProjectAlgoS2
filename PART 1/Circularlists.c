// circularLists.c
#include "circularLists.h"


 //--------CIRCULAR LINKEDLIST FUNCTIONS-----------

//FUNCTION TO CREATE NODE:
CLogEntry* createCNode(int id, const char* timestamp, int severity, const char* message) {
    CLogEntry* newNode = (CLogEntry*)malloc(sizeof(CLogEntry));
    newNode->id = id;
    strcpy(newNode->timestamp, timestamp);
    newNode->severity = severity;
    strcpy(newNode->message, message);
    newNode->next = NULL;
    return newNode;
}

// 1) FUNCTION TO INSERT NODE INTO A CIRCULAR LINKED LIST :

CLogEntry* insertCircular(CLogEntry* tail, int id, const char* timestamp, int severity, const char* message) {
    CLogEntry* newNode = createCNode(id, timestamp, severity, message);
    if (!tail) {
        newNode->next = newNode;
        return newNode;
    }
    newNode->next = tail->next;
    tail->next = newNode;
    return newNode; // new tail
}

// 2)FUNCTION TO INSERT NODE BY POSITION INTO A CIRCULAR LINKED LIST :

CLogEntry* insertAtPositionCircular(CLogEntry* tail, int position, int id, const char* timestamp, int severity, const char* message) {
    if (!tail || position <= 0) return insertCircular(tail, id, timestamp, severity, message);
    CLogEntry* newNode = createCNode(id, timestamp, severity, message);
    CLogEntry* curr = tail->next;
    for (int i = 0; i < position - 1 && curr != tail; i++) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
    if (curr == tail) tail = newNode;
    return tail;
}

// 3) FUNCTION TO DELETE NODE BY ID IN CIRCULAR LINKEDLIST:

CLogEntry* deleteByIDCircular(CLogEntry* tail, int id) {
    if (!tail) return NULL;
    CLogEntry *curr = tail->next, *prev = tail;
    do {
        if (curr->id == id) {
            if (curr == tail) tail = prev;
            if (curr == tail->next && curr == tail) {
                free(curr);
                return NULL;
            }
            prev->next = curr->next;
            free(curr);
            return tail;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != tail->next);
    return tail;
}

// 4) FUNCTION TO DELETE FIRST NODE OF A CIRCULAR LINKEDLIST:

CLogEntry* deleteFirstCircular(CLogEntry* tail) {
    if (!tail) return NULL;
    CLogEntry* head = tail->next;
    if (head == tail) {
        free(head);
        return NULL;
    }
    tail->next = head->next;
    free(head);
    return tail;
}

//5) FUNCTION TO DELETE LAST NODE OF A CIRCULAR LINKEDLIST:

CLogEntry* deleteLastCircular(CLogEntry* tail) {
    if (!tail) return NULL;
    CLogEntry *curr = tail->next, *prev = tail;
    while (curr->next != tail->next) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == prev) {
        free(curr);
        return NULL;
    }
    prev->next = tail->next;
    free(curr);
    return prev;
}

 // 6) FUNCTION TO SEARCH BY ID IN CIRCULAR LINKEDLIST :

CLogEntry* searchByIDCircular(CLogEntry* tail, int id) {
    if (!tail) return NULL;
    CLogEntry* curr = tail->next;
    do {
        if (curr->id == id) return curr;
        curr = curr->next;
    } while (curr != tail->next);
    return NULL;
}

// 7) FUNCTION TO SEARCH NODE BY TIMESTAMP IN CIRCULARLIST:

CLogEntry* searchByTimestampCircular(CLogEntry* tail, const char* timestamp) {
    if (!tail) return NULL;
    CLogEntry* curr = tail->next;
    do {
        if (strcmp(curr->timestamp, timestamp) == 0) return curr;
        curr = curr->next;
    } while (curr != tail->next);
    return NULL;
}

// 8) FUNCTION TO SEARCH NODE BY KEYWORD IN CIRCULAR LIST:

CLogEntry* searchByKeywordCircular(CLogEntry* tail, const char* keyword) {
    if (!tail) return NULL;
    CLogEntry* curr = tail->next;
    do {
        if (strstr(curr->message, keyword)) return curr;
        curr = curr->next;
    } while (curr != tail->next);
    return NULL;
}

// "FUNCTION TO COMPARE TWO TIMESTAMP STRINGS :

int compareCTimestamps(const char* a, const char* b) {
    return strcmp(a, b);
}

// 9) FUNCTION TO SORT CIRCULAR LIST BY TIMESTAMP :

CLogEntry* sortByDateCircular(CLogEntry* tail) {
    if (!tail || tail->next == tail) return tail;
    CLogEntry* start = tail->next;
    for (CLogEntry* i = start; i->next != start; i = i->next) {
        for (CLogEntry* j = i->next; j != start; j = j->next) {
            if (compareCTimestamps(i->timestamp, j->timestamp) > 0) {
                int tmpId = i->id; i->id = j->id; j->id = tmpId;
                char tmpTime[20]; strcpy(tmpTime, i->timestamp); strcpy(i->timestamp, j->timestamp); strcpy(j->timestamp, tmpTime);
                int tmpSeverity = i->severity; i->severity = j->severity; j->severity = tmpSeverity;
                char tmpMsg[100]; strcpy(tmpMsg, i->message); strcpy(i->message, j->message); strcpy(j->message, tmpMsg);
            }
        }
    }
    return tail;
}

// 10) FUNCTION TO SORT CIRCULAR LIST BY SEVERITY LEVEL :

CLogEntry* sortBySeverityCircular(CLogEntry* tail) {
    if (!tail || tail->next == tail) return tail;
    CLogEntry* start = tail->next;
    for (CLogEntry* i = start; i->next != start; i = i->next) {
        for (CLogEntry* j = i->next; j != start; j = j->next) {
            if (i->severity > j->severity) {
                int tmpId = i->id; i->id = j->id; j->id = tmpId;
                char tmpTime[20]; strcpy(tmpTime, i->timestamp); strcpy(i->timestamp, j->timestamp); strcpy(j->timestamp, tmpTime);
                int tmpSeverity = i->severity; i->severity = j->severity; j->severity = tmpSeverity;
                char tmpMsg[100]; strcpy(tmpMsg, i->message); strcpy(i->message, j->message); strcpy(j->message, tmpMsg);
            }
        }
    }
    return tail;
}

// 11) FUNCTION TO REVERSE A CIRCULAR LIST :
CLogEntry* reverseCircular(CLogEntry* tail) {
    if (!tail || tail->next == tail) return tail;
    CLogEntry *prev = tail, *curr = tail->next, *next;
    do {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } while (curr != tail);
    tail->next = prev;
    return curr;
}

// 12) FUNCTION TO COUNT NODES IN A CIRCULAR LIST :

int countLogsCircular(CLogEntry* tail) {
    if (!tail) return 0;
    int count = 0;
    CLogEntry* curr = tail->next;
    do {
        count++;
        curr = curr->next;
    } while (curr != tail->next);
    return count;
}

// 13) PROCEDURE TO PRINT ALL NODES OF A CIRCULAR LIST:

void traverseCircular(CLogEntry* tail) {
    if (!tail) return;
    CLogEntry* temp = tail->next;
    do {
        printf("ID: %d, Time: %s, Severity: %d, Message: %s\n", temp->id, temp->timestamp, temp->severity, temp->message);
        temp = temp->next;
    } while (temp != tail->next);
}

// 14) FUNCTION TO MAINTAIN FIXED SIZE CIRCULAR BUFFER:

CLogEntry* createFixedSizeBuffer(CLogEntry* tail, int id, const char* timestamp, int severity, const char* message, int* size) {
    if (*size < MAX_LOGS) {
        tail = insertCircular(tail, id, timestamp, severity, message);
        (*size)++;
    } else {
        CLogEntry* head = tail->next;
        CLogEntry* temp = head;
        head = head->next;
        tail->next = head;
        free(temp);
        tail = insertCircular(tail, id, timestamp, severity, message);
    }
    return tail;
}


// 15) FUNCTION TO DETECT IF THERE IS A CYCLE IN A CIRCULAR LIST :

int detectCycle(CLogEntry* head) {
    if (!head) return 0;
    CLogEntry *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1;
    }
    return 0;
}
