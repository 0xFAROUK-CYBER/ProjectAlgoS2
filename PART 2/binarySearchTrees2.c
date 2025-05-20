#include "binarySearchTrees2.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int countVowels(const char *word) {
    int count = 0;
    while (*word) {
        char c = tolower(*word);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            count++;
        word++;
    }
    return count;
}

int compareWords(const char *a, const char *b) {
    return strcmp(a, b);
}

TTree* insertTree(TTree *root, WordData data) {
    if (!root) {
        TTree *node = (TTree *)malloc(sizeof(TTree));
        node->data = data;
        node->left = node->right = NULL;
        return node;
    }

    if (compareWords(data.word, root->data.word) < 0)
        root->left = insertTree(root->left, data);
    else
        root->right = insertTree(root->right, data);
        
    return root;
}

TStack* popStack(TStack **stk) {
    if (!*stk) return NULL;
    TStack *top = *stk;
    *stk = (*stk)->next;
    return top;
}

TTree* toTree(TStack *stk) {
    TTree *root = NULL;
    while (stk) {
        TStack *top = popStack(&stk);
        root = insertTree(root, top->data);
        free(top);
    }
    return root;
}

TTree* fillTree(FILE *f) {
    if (!f) return NULL;
    TTree *root = NULL;
    char word[50], synonym[50], antonym[50];
    
    while (fscanf(f, "%s %s %s", word, synonym, antonym) == 3) {
        WordData data;
        strcpy(data.word, word);
        strcpy(data.synonym, synonym);
        strcpy(data.antonym, antonym);
        data.charCount = strlen(word);
        data.vowelCount = countVowels(word);
        root = insertTree(root, data);
    }
    return root;
}

TTree* getInfWordTree(TTree *tr, char *word) {
    if (!tr) return NULL;
    int cmp = compareWords(word, tr->data.word);
    if (cmp == 0) return tr;
    else if (cmp < 0) return getInfWordTree(tr->left, word);
    else return getInfWordTree(tr->right, word);
}

TTree* AddWordBST(TTree *tr, char *word, char *syne, char *anton) {
    if (!tr) {
        TTree *node = (TTree*)malloc(sizeof(TTree));
        strcpy(node->data.word, word);
        strcpy(node->data.synonym, syne);
        strcpy(node->data.antonym, anton);
        node->data.charCount = strlen(word);
        node->data.vowelCount = countVowels(word);
        node->left = node->right = NULL;
        return node;
    }

    int cmp = compareWords(word, tr->data.word);
    if (cmp < 0) {
        tr->left = AddWordBST(tr->left, word, syne, anton);
    } else if (cmp > 0) {
        tr->right = AddWordBST(tr->right, word, syne, anton);
    }
    return tr;
}

// Helper to find minimum node in right subtree
TTree* findMinNode(TTree* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

TTree* deleteWordBST(TTree *tr, char *word) {
    if (!tr) return NULL;
    int cmp = compareWords(word, tr->data.word);
    if (cmp < 0) {
        tr->left = deleteWordBST(tr->left, word);
    } else if (cmp > 0) {
        tr->right = deleteWordBST(tr->right, word);
    } else {
        // Node to delete found
        if (!tr->left) {
            TTree *rightChild = tr->right;
            free(tr);
            return rightChild;
        } else if (!tr->right) {
            TTree *leftChild = tr->left;
            free(tr);
            return leftChild;
        } else {
            // Node with two children
            TTree *minRight = findMinNode(tr->right);
            tr->data = minRight->data;
            tr->right = deleteWordBST(tr->right, minRight->data.word);
        }
    }
    return tr;
}

TTree* UpdateWordBST(TTree *tr, char *word, char *syne, char *anton) {
    if (!tr) return NULL;

    int cmp = compareWords(word, tr->data.word);
    if (cmp == 0) {
        strcpy(tr->data.synonym, syne);
        strcpy(tr->data.antonym, anton);
    } else if (cmp < 0) {
        tr->left = UpdateWordBST(tr->left, word, syne, anton);
    } else {
        tr->right = UpdateWordBST(tr->right, word, syne, anton);
    }
    return tr;
}

void TraversalBSTinOrder(TTree *tr) {
    if (!tr) return;
    TraversalBSTinOrder(tr->left);
    printf("%s (Synonym: %s, Antonym: %s, Chars: %d, Vowels: %d)\n",
           tr->data.word, tr->data.synonym, tr->data.antonym, tr->data.charCount, tr->data.vowelCount);
    TraversalBSTinOrder(tr->right);
}

void TraversalBSTpreOrder(TTree *tr) {
    if (!tr) return;
    printf("%s (Synonym: %s, Antonym: %s, Chars: %d, Vowels: %d)\n",
           tr->data.word, tr->data.synonym, tr->data.antonym, tr->data.charCount, tr->data.vowelCount);
    TraversalBSTpreOrder(tr->left);
    TraversalBSTpreOrder(tr->right);
}

void TraversalBSTpostOrder(TTree *tr) {
    if (!tr) return;
    TraversalBSTpostOrder(tr->left);
    TraversalBSTpostOrder(tr->right);
    printf("%s (Syn: %s, Ant: %s, Chars: %d, Vowels: %d)\n",
           tr->data.word, tr->data.synonym, tr->data.antonym,
           tr->data.charCount, tr->data.vowelCount);
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}


int heightBST(TTree *tr) {
    if (!tr) return 0;
    return 1 + max(heightBST(tr->left), heightBST(tr->right));
}

int sizeBST(TTree *tr) {
    if (!tr) return 0;
    return 1 + sizeBST(tr->left) + sizeBST(tr->right);
}

void HighSizeBST(TTree *tr) {
    int h = heightBST(tr);
    int s = sizeBST(tr);
    printf("Height of BST: %d\n", h);
    printf("Size (number of nodes) of BST: %d\n", s);
}

TTree *LowestCommonAncestor(TTree *tr, char *word1, char *word2) {
    if (!tr) return NULL;
    int cmp1 = compareWords(word1, tr->data.word);
    int cmp2 = compareWords(word2, tr->data.word);

    // If both words are smaller, go left
    if (cmp1 < 0 && cmp2 < 0)
        return LowestCommonAncestor(tr->left, word1, word2);

    // If both words are greater, go right
    if (cmp1 > 0 && cmp2 > 0)
        return LowestCommonAncestor(tr->right, word1, word2);

    // Otherwise, current node is LCA
    return tr;
}

int CountNodesRanges(TTree *tr, int l, int h) {
    if (!tr) return 0;

    int count = 0;
    if (tr->data.charCount >= l && tr->data.charCount <= h)
        count = 1;
    return count + CountNodesRanges(tr->left, l, h) + CountNodesRanges(tr->right, l, h);
}

// Helper: Find min node in subtree

TTree* inOrderSuccessor(TTree *tr, char *word) {
    TTree *successor = NULL;
    TTree *current = tr;

    while (current) {
        int cmp = compareWords(word, current->data.word);
        if (cmp < 0) {
            successor = current;   // potential successor
            current = current->left;
        }
        else if (cmp > 0) {
            current = current->right;
        }
        else {
            // Node found
            if (current->right) {
                successor = findMinNode(current->right);
            }
            break;
        }
    }

    return successor;
}

TTree* BSTMirror(TTree *tr) {
    if (!tr) return NULL;

    TTree *mirrorNode = malloc(sizeof(TTree));
    if (!mirrorNode) return NULL; // handle malloc fail

    // Copy data
    mirrorNode->data = tr->data;

    // Recursively mirror right and left swapped
    mirrorNode->left = BSTMirror(tr->right);
    mirrorNode->right = BSTMirror(tr->left);

    return mirrorNode;
}

// Helper function to get height and check balance simultaneously
int checkHeightBalance(TTree *tr, bool *isBalanced) {
    if (!tr) return 0;

    int leftHeight = checkHeightBalance(tr->left, isBalanced);
    int rightHeight = checkHeightBalance(tr->right, isBalanced);

    if (abs(leftHeight - rightHeight) > 1) {
        *isBalanced = false;
    }

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

bool isBalancedBST(TTree *tr) {
    bool balanced = true;
    checkHeightBalance(tr, &balanced);
    return balanced;
}

// Helpers:

void inorderToArray(TTree *tr, WordData arr[], int *index) {
    if (!tr) return;
    inorderToArray(tr->left, arr, index);
    arr[(*index)++] = tr->data;
    inorderToArray(tr->right, arr, index);
}

TTree* sortedArrayToBST(WordData arr[], int start, int end) {
    if (start > end) return NULL;

    int mid = (start + end) / 2;
    TTree *node = malloc(sizeof(TTree));
    if (!node) return NULL;

    node->data = arr[mid];
    node->left = sortedArrayToBST(arr, start, mid - 1);
    node->right = sortedArrayToBST(arr, mid + 1, end);

    return node;
}

TTree *BTSMerge(TTree *tr1, TTree *tr2) {
    int size1 = sizeBST(tr1);
    int size2 = sizeBST(tr2);
    int totalSize = size1 + size2;

    WordData *arr1 = malloc(size1 * sizeof(WordData));
    WordData *arr2 = malloc(size2 * sizeof(WordData));
    if (!arr1 || !arr2) return NULL; // handle malloc fail

    int index1 = 0, index2 = 0;
    inorderToArray(tr1, arr1, &index1);
    inorderToArray(tr2, arr2, &index2);

    // Merge sorted arrays
    WordData *merged = malloc(totalSize * sizeof(WordData));
    if (!merged) return NULL;

    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (strcmp(arr1[i].word, arr2[j].word) < 0) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }
    while (i < size1) merged[k++] = arr1[i++];
    while (j < size2) merged[k++] = arr2[j++];

    // Build balanced BST from merged array
    TTree *mergedBST = sortedArrayToBST(merged, 0, totalSize - 1);

    free(arr1);
    free(arr2);
    free(merged);

    return mergedBST;
}

