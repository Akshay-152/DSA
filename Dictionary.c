
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char word[50];
    char meaning[100];
    struct Node *left, *right;
};

struct Node* createNode(char word[], char meaning[]) {
    struct Node *newNode = malloc(sizeof(struct Node));

    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);
    newNode->left = newNode->right = NULL;

    return newNode;
}

struct Node* insert(struct Node *root, char word[], char meaning[]) {
    if (root == NULL)
        return createNode(word, meaning);

    int cmp = strcmp(word, root->word);

    if (cmp < 0)
        root->left = insert(root->left, word, meaning);
    else if (cmp > 0)
        root->right = insert(root->right, word, meaning);
    else
        printf("Word already exists.\n");

    return root;
}

void search(struct Node *root, char word[]) {
    if (root == NULL) {
        printf("Word not found.\n");
        return;
    }

    int cmp = strcmp(word, root->word);

    if (cmp == 0)
        printf("Meaning: %s\n", root->meaning);
    else if (cmp < 0)
        search(root->left, word);
    else
        search(root->right, word);
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%-15s : %s\n", root->word, root->meaning);
        inorder(root->right);
    }
}

int main() {
    struct Node *root = NULL;
    int choice;
    char word[50], meaning[100];

    while (1) {
        printf("\n--- DICTIONARY USING BST ---\n");
        printf("1. Insert word and meaning\n");
        printf("2. Search for a word\n");
        printf("3. Display dictionary\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter word: ");
                scanf("%49s", word);

                printf("Enter meaning: ");
                scanf(" %99[^\n]", meaning);

                root = insert(root, word, meaning);
                break;

            case 2:
                printf("Enter word to search: ");
                scanf("%49s", word);
                search(root, word);
                break;

            case 3:
                if (root == NULL)
                    printf("Dictionary is empty.\n");
                else {
                    printf("\nWord           : Meaning\n");
                    printf("-------------------------------\n");
                    inorder(root);
                }
                break;

            case 4:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
