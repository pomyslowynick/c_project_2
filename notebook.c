#include "notebook.h"
#include "note.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct node {
	struct note* data;
	struct node* next;
};

/**
 * Forward declaration of the notebook struct.
 */
struct notebook {
    struct node* head;
};

/**
 * Dynamically allocates a single notebook struct. A note comprises a  linked-list
 * of notes.
 */
struct notebook* createNotebook() {
    struct notebook *notebookPtr = (struct notebook*)malloc(sizeof(struct notebook));
    (*notebookPtr).head = NULL;
    return notebookPtr;
}

/**
 * Adds the given note to the end of the given notebook's note list.
 */
void addNote(struct notebook *notebook, struct note *note) {
    struct node *currentNode = (*notebook).head;
    // printf("%d\n", (currentNode == NULL));
    struct node* newNode = (struct node*)malloc(1 * sizeof(struct node));
    (*newNode).data = note;
    (*newNode).next = NULL;
    if (currentNode == NULL) {
        (*notebook).head = newNode;
    }
    else {
        while ((*currentNode).next != NULL) {
            currentNode = (*currentNode).next;
        }
        (*currentNode).next = newNode;
    }
}

/**
 * Removes the given note from the given notebook's note list, if it is present.
 */
void removeNote(struct notebook *notebook, struct note *note) {
    struct node *currentNode = (*notebook).head;
    struct node *previousNode = NULL;

    if((*currentNode).data == note) {
        (*notebook).head = (*currentNode).next;
    } else {
        while((currentNode != NULL) && ((*currentNode).data != note)) {
            previousNode = currentNode;
            currentNode = (*currentNode).next;
        }
        if(currentNode == NULL) {
            printf("There is no such note in notebook\n");
        }
        else {
            (*previousNode).next = (*currentNode).next;
            free(currentNode);
        }
    }
    
    

}

/**
 * Searches the given notebook's note list for the first note whose content contains the
 * given string. If such a note exists, a pointer to same is returned; else this funcion returns NULL. 
 */
struct note* findByContent(struct notebook *notebook, char *str) {
    struct node *currentNode = (*notebook).head;
    while (currentNode != NULL) {
        char *currentContents = getContents((*currentNode).data);
        // printf("%s\n", currentTitle);
        char *searchResult = strstr(currentContents, str);

        if(searchResult) {
            return (*currentNode).data;
        }
        currentNode = (*currentNode).next;
    }
    // printf("%s\n", getTitle((*currentNode).data));
    return NULL;

}

/**
 * Searches the given notebook's note list for the first note whose title contains the
 * given string. If such a note exists, a pointer to same is returned; else this funcion returns NULL. 
 */
struct note* findByTitle(struct notebook *notebook, char *str) {
    struct node *currentNode = (*notebook).head;
    while (currentNode != NULL) {
        char *currentTitle = getTitle((*currentNode).data);
        // printf("%s\n", currentTitle);
        if(currentTitle == str) {
            return (*currentNode).data;
        }
        currentNode = (*currentNode).next;
    }
    // printf("%s\n", getTitle((*currentNode).data));
    return NULL;

}

/**
 * Returns the number of notes contained in the given notebook's note list.
 */
int countNotes(struct notebook* notebook) {
    int i = 0;
    struct node *currentNode = (*notebook).head;

    while (currentNode != NULL) {
        currentNode = (*currentNode).next;
        i++;
    }
    return i;
}

/**
 * Removes all notes from the given notebook's note list.
 */
void clearNotes(struct notebook *notebook) {
    struct node *currentNode = (*notebook).head;
    struct node *nextNode = NULL;
    while (currentNode != NULL) {
        nextNode = (*currentNode).next;
        free(currentNode);

        currentNode = nextNode;
    }
    (*notebook).head = NULL;
}

void swap(struct node *a, struct node *b) 
{ 
// to swap two nodes in a linked link, just swap their data pointers 
// leave the list node order as-is!
    struct note* temp = (*a).data; 
    (*a).data = (*b).data; 
    (*b).data = temp; 
} 


/**
 * Sorts all notes in the given notebook's note list. Notes are sorted by priority; a lower priority 
 * value should appear earlier in the sorted list, i.e. a note with priority 1 will appear before a note with priority 2.
 * Any sort algorithm may be applied. Bubblesort is the suggested sort implementation.
 */
void sortByPriority(struct notebook *notebook) {
    // start at the first node pointed to by the list head
    struct node *startNode = (*notebook).head;

    // for an empty list, we have nothing to do
    if(!startNode) {
        return;
    }

    // iterate the list repeatedly until there is no swap performed in a given iteration
    // at this point the list is sorted
    int done = 1; 
    do {
        // start of loop; set done to 1 / true 
        done = 1;

        // start from the first node in the list
        struct node *currentNode = startNode; 

        // move through the list until we hit a node with no subsequent node
        while (currentNode != NULL) { 

            // getNodeRank will get a numeric value from the node data
            int rankL = getPriority((*currentNode).data);
            static int rankR = 100;
            if ((*currentNode).next != NULL) {
                rankR = getPriority(currentNode->next->data);

            }

            // if nodes are out of order, swap them, set the done flag to false / 0
            if (rankL > rankR) { 
                swap(currentNode, currentNode->next); 
                done = 0;
            } 

            // move to the next node in the list
            currentNode = currentNode->next; 
        } 
    } while (!done); 
}

/**
 * Returns a pointer to the note at the given index in the given notebook's note list. If an invalid index is passed to 
 * this function it will return NULL.
 */
struct note* getNoteAt(struct notebook *notebook, int index) {
    struct node *currentNode = (*notebook).head;
    int currentIndex = 0;
    while ((currentNode != NULL) && (currentIndex < index)) {
		currentNode = (*currentNode).next;
		currentIndex++;
	}

    if (currentNode == NULL) {
        return NULL;
    }
	else {
        return (*currentNode).data;
	}

}
