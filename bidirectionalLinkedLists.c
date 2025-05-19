// bidirectionalLinkedLists.c
#include "bidirectionalLinkedLists.h"

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

DLogEntry* insertDLogAtEnd(DLogEntry* head, int id, const char* timestamp, int severity, const char* message) {
    DLogEntry* newNode = createDNode(id, timestamp, severity, message);
    if (!head) return newNode;
    DLogEntry* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

DLogEntry* moveForward(DLogEntry* head, int steps) {
    while (head && steps > 0) {
        head = head->next;
        steps--;
    }
    return head;
}

DLogEntry* moveBackward(DLogEntry* tail, int steps) {
    while (tail && steps > 0) {
        tail = tail->prev;
        steps--;
    }
    return tail;
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

DLogEntry* mergeDLists(DLogEntry* list1, DLogEntry* list2) {
    if (!list1) return list2;
    if (!list2) return list1;
    DLogEntry* temp = list1;
    while (temp->next) temp = temp->next;
    temp->next = list2;
    list2->prev = temp;
    return list1;
}
