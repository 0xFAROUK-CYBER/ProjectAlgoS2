// bidirectionalLinkedLists.c
#include "bidirectionalLinkedLists.h"


//----------BIDIRECTIONAL LINKEDLISTS FUNCTIONS------*

DLogEntry* createDNode(int id, const char* timestamp, int severity, const char* message) {
    DLogEntry* newNode = (DLogEntry*)malloc(sizeof(DLogEntry));
    newNode->id = id;
    strcpy(newNode->timestamp, timestamp);
    newNode->severity = severity;
    strcpy(newNode->message, message);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

DLogEntry* insertAtBeginningD(DLogEntry* head, int id, const char* timestamp, int severity, const char* message) {
    DLogEntry* newNode = createDNode(id, timestamp, severity, message);
    newNode->next = head;
    if (head) head->prev = newNode;
    return newNode;
}

DLogEntry* insertAtEndD(DLogEntry* head, int id, const char* timestamp, int severity, const char* message) {
    DLogEntry* newNode = createDNode(id, timestamp, severity, message);
    if (!head) return newNode;
    DLogEntry* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

DLogEntry* insertAtPositionD(DLogEntry* head, int position, int id, const char* timestamp, int severity, const char* message) {
    if (position <= 0 || !head) return insertAtBeginningD(head, id, timestamp, severity, message);
    DLogEntry* temp = head;
    for (int i = 0; i < position - 1 && temp->next; i++) temp = temp->next;
    if (!temp->next) return insertAtEndD(head, id, timestamp, severity, message);
    DLogEntry* newNode = createDNode(id, timestamp, severity, message);
    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
    return head;
}

DLogEntry* deleteByIDD(DLogEntry* head, int id) {
    DLogEntry* temp = head;
    while (temp && temp->id != id) temp = temp->next;
    if (!temp) return head;
    if (temp->prev) temp->prev->next = temp->next;
    else head = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    free(temp);
    return head;
}

DLogEntry* deleteFirstD(DLogEntry* head) {
    if (!head) return NULL;
    DLogEntry* next = head->next;
    if (next) next->prev = NULL;
    free(head);
    return next;
}

DLogEntry* deleteLastD(DLogEntry* head) {
    if (!head) return NULL;
    DLogEntry* temp = head;
    while (temp->next) temp = temp->next;
    if (temp->prev) temp->prev->next = NULL;
    else head = NULL;
    free(temp);
    return head;
}

DLogEntry* deleteMiddleNode(DLogEntry* head) {
    if (!head || !head->next) {
        free(head);
        return NULL;
    }
    DLogEntry *slow = head, *fast = head;
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    if (slow->prev) slow->prev->next = slow->next;
    if (slow->next) slow->next->prev = slow->prev;
    if (slow == head) head = slow->next;
    free(slow);
    return head;
}

DLogEntry* searchByIDD(DLogEntry* head, int id) {
    while (head && head->id != id) head = head->next;
    return head;
}

DLogEntry* searchByTimestampD(DLogEntry* head, const char* timestamp) {
    while (head && strcmp(head->timestamp, timestamp) != 0) head = head->next;
    return head;
}

DLogEntry* searchByKeywordD(DLogEntry* head, const char* keyword) {
    while (head) {
        if (strstr(head->message, keyword)) return head;
        head = head->next;
    }
    return NULL;
}

int compareDTimestamps(const char* a, const char* b) {
    return strcmp(a, b);
}

DLogEntry* sortByDateD(DLogEntry* head) {
    if (!head || !head->next) return head;
    for (DLogEntry* i = head; i; i = i->next) {
        for (DLogEntry* j = i->next; j; j = j->next) {
            if (compareDTimestamps(i->timestamp, j->timestamp) > 0) {
                DLogEntry temp = *i;
                *i = *j;
                *j = temp;
            }
        }
    }
    return head;
}

DLogEntry* sortBySeverityD(DLogEntry* head) {
    if (!head || !head->next) return head;
    for (DLogEntry* i = head; i; i = i->next) {
        for (DLogEntry* j = i->next; j; j = j->next) {
            if (i->severity > j->severity) {
                DLogEntry temp = *i;
                *i = *j;
                *j = temp;
            }
        }
    }
    return head;
}

DLogEntry* reverseListD(DLogEntry* head) {
    DLogEntry *temp = NULL, *curr = head;
    while (curr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    if (temp) head = temp->prev;
    return head;
}

int countLogsD(DLogEntry* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

DLogEntry* moveForward(DLogEntry* node, int steps) {
    while (node && steps-- > 0) node = node->next;
    return node;
}

DLogEntry* moveBackward(DLogEntry* node, int steps) {
    while (node && steps-- > 0) node = node->prev;
    return node;
}

DLogEntry* mergeDLists(DLogEntry* list1, DLogEntry* list2) {
    if (!list1) return list2;
    if (!list2) return list1;
    DLogEntry* temp = list1;
    while (temp->next) temp = temp->next;
    temp->next = list2;
    list2->prev = temp;
    return list1;
}
