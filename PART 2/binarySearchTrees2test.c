
#include "binarySearchTrees2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void displayMenu() {
    printf("\n\n=== Binary Search Tree Operations ===\n");
    printf("1. Load words from file\n");
    printf("2. Search for word information\n");
    printf("3. Add new word\n");
    printf("4. Delete word\n");
    printf("5. Update word\n");
    printf("6. Display in-order traversal\n");
    printf("7. Display pre-order traversal\n");
    printf("8. Display post-order traversal\n");
    printf("9. Get tree height and size\n");
    printf("10. Find lowest common ancestor\n");
    printf("11. Count nodes in character range\n");
    printf("12. Find in-order successor\n");
    printf("13. Create mirror tree\n");
    printf("14. Check if tree is balanced\n");
    printf("15. Merge two BSTs\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void displayWordInfo(TTree* node) {
    if (node) {
        printf("Word: %s\n", node->data.word);
        printf("Synonym: %s\n", node->data.synonym);
        printf("Antonym: %s\n", node->data.antonym);
        printf("Character count: %d\n", node->data.charCount);
        printf("Vowel count: %d\n", node->data.vowelCount);
    } else {
        printf("Word not found in tree.\n");
    }
}

TTree* loadSecondTree() {
    char filename[100];
    printf("Enter filename for second tree: ");
    scanf("%s", filename);
    
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Error opening file %s\n", filename);
        return NULL;
    }
    
    TTree* tree = fillTree(f);
    fclose(f);
    printf("Loaded %d words from %s\n", sizeBST(tree), filename);
    return tree;
}

int main() {
    TTree* tree = NULL;
    TTree* mirror = NULL;
    TTree* secondTree = NULL;
    TTree* mergedTree = NULL;
    char filename[100];
    int choice;
    
    printf("=== Binary Search Tree Test System ===\n");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: { // Load words from file
                printf("Enter filename: ");
                scanf("%s", filename);
                
                FILE* f = fopen(filename, "r");
                if (!f) {
                    printf("Error opening file %s\n", filename);
                    break;
                }
                
                tree = fillTree(f);
                fclose(f);
                printf("Loaded %d words from %s\n", sizeBST(tree), filename);
                break;
            }
                
            case 2: { // Search for word
                char word[50];
                printf("Enter word to search: ");
                scanf("%s", word);
                TTree* result = getInfWordTree(tree, word);
                displayWordInfo(result);
                break;
            }
                
            case 3: { // Add new word
                char word[50], syn[50], ant[50];
                printf("Enter word: ");
                scanf("%s", word);
                printf("Enter synonym: ");
                scanf("%s", syn);
                printf("Enter antonym: ");
                scanf("%s", ant);
                tree = AddWordBST(tree, word, syn, ant);
                printf("Word '%s' added to tree\n", word);
                break;
            }
                
            case 4: { // Delete word
                char word[50];
                printf("Enter word to delete: ");
                scanf("%s", word);
                tree = deleteWordBST(tree, word);
                printf("Word '%s' deleted from tree\n", word);
                break;
            }
                
            case 5: { // Update word
                char word[50], syn[50], ant[50];
                printf("Enter word to update: ");
                scanf("%s", word);
                printf("Enter new synonym: ");
                scanf("%s", syn);
                printf("Enter new antonym: ");
                scanf("%s", ant);
                tree = UpdateWordBST(tree, word, syn, ant);
                printf("Word '%s' updated\n", word);
                break;
            }
                
            case 6: // In-order traversal
                printf("\nIn-order traversal:\n");
                TraversalBSTinOrder(tree);
                break;
                
            case 7: // Pre-order traversal
                printf("\nPre-order traversal:\n");
                TraversalBSTpreOrder(tree);
                break;
                
            case 8: // Post-order traversal
                printf("\nPost-order traversal:\n");
                TraversalBSTpostOrder(tree);
                break;
                
            case 9: // Tree height and size
                HighSizeBST(tree);
                break;
                
            case 10: { // Lowest common ancestor
                char word1[50], word2[50];
                printf("Enter first word: ");
                scanf("%s", word1);
                printf("Enter second word: ");
                scanf("%s", word2);
                TTree* lca = LowestCommonAncestor(tree, word1, word2);
                printf("Lowest common ancestor: %s\n", lca ? lca->data.word : "None");
                break;
            }
                
            case 11: { // Count nodes in range
                int low, high;
                printf("Enter lower bound: ");
                scanf("%d", &low);
                printf("Enter upper bound: ");
                scanf("%d", &high);
                int count = CountNodesRanges(tree, low, high);
                printf("Number of nodes with %d-%d characters: %d\n", low, high, count);
                break;
            }
                
            case 12: { // In-order successor
                char word[50];
                printf("Enter word: ");
                scanf("%s", word);
                TTree* successor = inOrderSuccessor(tree, word);
                printf("In-order successor: ");
                displayWordInfo(successor);
                break;
            }
                
            case 13: { // Create mirror tree
                if (mirror) {
                    // Free previous mirror if exists
                    // Need to implement freeTree function
                }
                mirror = BSTMirror(tree);
                printf("Mirror tree created. In-order traversal:\n");
                TraversalBSTinOrder(mirror);
                break;
            }
                
            case 14: // Check balance
                printf("Tree is %sbalanced\n", isBalancedBST(tree) ? "" : "not ");
                break;
                
            case 15: { // Merge trees
                secondTree = loadSecondTree();
                if (secondTree) {
                    mergedTree = BTSMerge(tree, secondTree);
                    printf("Trees merged. In-order traversal of merged tree:\n");
                    TraversalBSTinOrder(mergedTree);
                }
                break;
            }
                
            case 0: // Exit
                printf("Exiting program\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
        // Pause before continuing
        if (choice != 0) {
            printf("\nPress Enter to continue...");
            while (getchar() != '\n'); // Clear input buffer
            getchar(); // Wait for Enter
        }
        
    } while (choice != 0);
    
    // TODO: Add memory cleanup for all trees
    
    return 0;
}