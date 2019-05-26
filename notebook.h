#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include "note.h"

/**
 * Forward declaration of the notebook struct.
 */
struct node;
/**
 * Forward declaration of the notebook struct.
 */
struct notebook;

/**
 * Dynamically allocates a single notebook struct. A note comprises a  linked-list
 * of notes.
 */
struct notebook* createNotebook();

/**
 * Adds the given note to the end of the given notebook's note list.
 */
void addNote(struct notebook *notebook, struct note *note); 

/**
 * Removes the given note from the given notebook's note list, if it is present.
 */
void removeNote(struct notebook *notebook, struct note *note);

/**
 * Searches the given notebook's note list for the first note whose content contains the
 * given string. If such a note exists, a pointer to same is returned; else this funcion returns NULL. 
 */
struct note* findByContent(struct notebook *notebook, char *str);

/**
 * Searches the given notebook's note list for the first note whose title contains the
 * given string. If such a note exists, a pointer to same is returned; else this funcion returns NULL. 
 */
struct note* findByTitle(struct notebook *notebook, char *str);

/**
 * Returns the number of notes contained in the given notebook's note list.
 */
int countNotes(struct notebook *notebook);

/**
 * Removes all notes from the given notebook's note list.
 */
void clearNotes(struct notebook *notebook);

/**
 * Sorts all notes in the given notebook's note list. Notes are sorted by priority; a lower priority 
 * value should appear earlier in the sorted list, i.e. a note with priority 1 will appear before a note with priority 2.
 * Any sort algorithm may be applied. Bubblesort is the suggested sort implementation.
 */
void sortByPriority(struct notebook *notebook);

/**
 * Returns a pointer to the note at the given index in the given notebook's note list. If an invalid index is passed to 
 * this function it will return NULL.
 */
struct note* getNoteAt(struct notebook *notebook, int index);

#endif