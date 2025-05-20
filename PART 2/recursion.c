#include "recursion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Count how many times 'word' appears in the file linked list 'f'
int countWordOccurence(File *f, char *word) {
    if (f == NULL) return 0;
    int count = (strcmp(f->word, word) == 0) ? 1 : 0;
    return count + countWordOccurence(f->next, word);
}

// Remove all nodes with 'word' in the file linked list 'f'
File *removeWordOccurence(File *f, char *word) {
    if (f == NULL) return NULL;
    f->next = removeWordOccurence(f->next, word);
    if (strcmp(f->word, word) == 0) {
        File *temp = f->next;
        free(f->word);
        free(f);
        return temp;
    }
    return f;
}

// Replace all occurrences of 'word' with 'rep' in the file linked list 'f'
File *replaceWordOccurence(File *f, char *word, char *rep) {
    if (f == NULL) return NULL;
    if (strcmp(f->word, word) == 0) {
        free(f->word);
        f->word = strdup(rep);
    }
    f->next = replaceWordOccurence(f->next, word, rep);
    return f;
}

// Helper function to swap characters for permutation
void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

// Recursive helper to generate permutations of a string
void permute(char *word, int l, int r) {
    if (l == r) {
        printf("%s\n", word);
        return;
    }
    for (int i = l; i <= r; i++) {
        swap(&word[l], &word[i]);
        permute(word, l+1, r);
        swap(&word[l], &word[i]); // backtrack
    }
}

// Prints all permutations of 'word'
void wordPermutation(char *word) {
    permute(word, 0, strlen(word)-1);
}

// Recursive helper to generate subsequences
void subseqHelper(char *word, char *subseq, int i, int j) {
    if (word[i] == '\0') {
        subseq[j] = '\0';
        if (j > 0) // print only non-empty subsequences
            printf("%s\n", subseq);
        return;
    }
    // Include current character
    subseq[j] = word[i];
    subseqHelper(word, subseq, i+1, j+1);
    // Exclude current character
    subseqHelper(word, subseq, i+1, j);
}

// Generate and print all subsequences of 'word'
void subseqWord(char *word) {
    int len = strlen(word);
    char *subseq = malloc(len+1);
    subseqHelper(word, subseq, 0, 0);
    free(subseq);
}

// Find length of longest common subsequence recursively
int longestSubseqWord(char *word1, char *word2) {
    if (*word1 == '\0' || *word2 == '\0') return 0;
    if (*word1 == *word2)
        return 1 + longestSubseqWord(word1+1, word2+1);
    else {
        int l1 = longestSubseqWord(word1+1, word2);
        int l2 = longestSubseqWord(word1, word2+1);
        return (l1 > l2) ? l1 : l2;
    }
}

// Count distinct subsequences of 'word' recursively
// Using exponential approach (for small inputs)
int distinctSubseqWord(char *word) {
    if (*word == '\0') return 1; // empty subsequence
    int count = distinctSubseqWord(word+1) * 2;

    // Check for duplicates in the remaining substring
    for (char *p = word + 1; *p != '\0'; p++) {
        if (*p == *word) {
            count -= distinctSubseqWord(p + 1);
            break;
        }
    }
    return count;
}

// Check if 'word' is palindrome recursively
bool isPalindromeHelper(const char *word, int start, int end) {
    if (start >= end) return true;
    if (word[start] != word[end]) return false;
    return isPalindromeHelper(word, start + 1, end - 1);
}

bool isPalindromWord(char *word) {
    int len = strlen(word);
    return isPalindromeHelper(word, 0, len - 1);
}


