#include <stdio.h>
#include <stdlib.h>
//Cody Zheng
//Torosdagli
//Lab 10

struct Trie {
    int count;
    struct Trie *children[26];
};


void insert(struct Trie **ppTrie, char *word) {
    struct Trie *pTrie = *ppTrie;
    if (pTrie == NULL) {

        pTrie = (struct Trie *) calloc(1, sizeof(struct Trie));
        *ppTrie = pTrie;
    }
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {

            pTrie->children[index] = (struct Trie *) calloc(1, sizeof(struct Trie));
        }
        pTrie = pTrie->children[index];
    }

    pTrie->count++;
}


int numberOfOccurrences(struct Trie *pTrie, char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            return 0;
        }
        pTrie = pTrie->children[index];
    }

    return pTrie->count;
}


struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie != NULL) {
        for (int i = 0; i < 26; i++) {
            pTrie->children[i] = deallocateTrie(pTrie->children[i]);
        }
        free(pTrie);
    }
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
    }

    for (int i = 0; i < 5; i++) {
        int count = numberOfOccurrences(trie, pWords[i]);
        if (count > 0) {
            printf("\t%s : %d\n", pWords[i], count);

            struct Trie *pTrie = trie;
            for (int j = 0; pWords[i][j] != '\0'; j++) {
                int index = pWords[i][j] - 'a';
                pTrie = pTrie->children[index];
            }
            pTrie->count = 0;
        }
    }

    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
