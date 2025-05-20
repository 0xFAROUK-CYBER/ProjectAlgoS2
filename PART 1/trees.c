// trees.c
#include "trees.h"


//------------PART 1 TREES FUNCTIONS----------*


TLogEntry* createTNode(int id, const char* timestamp, int severity, const char* message) {
    TLogEntry* newNode = (TLogEntry*)malloc(sizeof(TLogEntry));
    newNode->id = id;
    strcpy(newNode->timestamp, timestamp);
    newNode->severity = severity;
    strcpy(newNode->message, message);
    newNode->left = newNode->right = NULL;
    return newNode;
}

int compareTimestamps(const char* a, const char* b) {
    return strcmp(a, b);
}

TLogEntry* insertBST(TLogEntry* root, int id, const char* timestamp, int severity, const char* message) {
    if (!root) return createTNode(id, timestamp, severity, message);
    if (compareTimestamps(timestamp, root->timestamp) < 0)
        root->left = insertBST(root->left, id, timestamp, severity, message);
    else
        root->right = insertBST(root->right, id, timestamp, severity, message);
    return root;
}

TLogEntry* findMin(TLogEntry* root) {
    while (root->left) root = root->left;
    return root;
}

TLogEntry* deleteBST(TLogEntry* root, const char* timestamp) {
    if (!root) return NULL;
    int cmp = compareTimestamps(timestamp, root->timestamp);
    if (cmp < 0) root->left = deleteBST(root->left, timestamp);
    else if (cmp > 0) root->right = deleteBST(root->right, timestamp);
    else {
        if (!root->left) {
            TLogEntry* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            TLogEntry* temp = root->left;
            free(root);
            return temp;
        }
        TLogEntry* temp = findMin(root->right);
        strcpy(root->timestamp, temp->timestamp);
        root->id = temp->id;
        root->severity = temp->severity;
        strcpy(root->message, temp->message);
        root->right = deleteBST(root->right, temp->timestamp);
    }
    return root;
}

TLogEntry* searchBST(TLogEntry* root, const char* timestamp) {
    if (!root || strcmp(root->timestamp, timestamp) == 0) return root;
    if (compareTimestamps(timestamp, root->timestamp) < 0)
        return searchBST(root->left, timestamp);
    else
        return searchBST(root->right, timestamp);
}

void inOrderTraversal(TLogEntry* root) {
    if (root) {
        inOrderTraversal(root->left);
        printf("%s\n", root->timestamp);
        inOrderTraversal(root->right);
    }
}

void preOrderTraversal(TLogEntry* root) {
    if (root) {
        printf("%s\n", root->timestamp);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void postOrderTraversal(TLogEntry* root) {
    if (root) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%s\n", root->timestamp);
    }
}

int countListNodes(TLogEntry* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->right;
    }
    return count;
}

TLogEntry* sortedListToBST(TLogEntry** headRef, int n) {
    if (n <= 0) return NULL;
    TLogEntry* left = sortedListToBST(headRef, n / 2);
    TLogEntry* root = *headRef;
    root->left = left;
    *headRef = (*headRef)->right;
    root->right = sortedListToBST(headRef, n - n / 2 - 1);
    return root;
}

void heapify(TLogEntry arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && compareTimestamps(arr[l].timestamp, arr[largest].timestamp) > 0)
        largest = l;
    if (r < n && compareTimestamps(arr[r].timestamp, arr[largest].timestamp) > 0)
        largest = r;
    if (largest != i) {
        TLogEntry temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void buildHeap(TLogEntry arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}
