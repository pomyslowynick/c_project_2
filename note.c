#include "note.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * Forward declaration of the note struct.
 */
struct note {
    char *title;
    char *contents;
    int priority;
};

/**
 * Dynamically allocates a single note struct. A note comprises a title string,
 * contents string, and a priority. Copies of the title and 
 * contents strings set on the note before returning a struct note pointer.
 */
struct note* createNote(char *title, char *contents, int priority) {
    struct note *y = (struct note*)malloc(sizeof(struct note));
    y->title = title;
    y->contents = contents;
    y->priority = priority;
    return y;
};

/**
 * Returns the priority of for the given note. The lower the integer
 * value, the higher the priority of the note.
 */
int getPriority(struct note *note) {
    return (*note).priority;
}

/**
 * Returns the title of the given note. 
 */
char* getTitle(struct note *note) {
    return (*note).title;
}

/**
 * Returns the contents of the given note. 
 */
char* getContents(struct note *note) {
    return (*note).contents;
}

/**
 * Returns the first line of content for the given note, i.e. all characters up
 * to but not including a line break character. 
 */
char* head(struct note *note) {
    char* content = (*note).contents;
    static char result[1000];
    int i = 0;
    for (;content[i] != '\n';i++)
    {
        result[i] = content[i];
        if(content[i + 1] == '\n') {
            result[i + 1] = '\0';
        }
    }
    return result;
}

/**
 * Returns the word count for the given note. Words are separated by whitespace 
 * or line-break characters; words can also by separated by punctuation characters such as period '.' 
 */
unsigned int getWordCount(struct note *note) {
    char* content = (*note).contents;
    int count = 0;
    int i = 0;
    for (;content[i] != '\0';i++)
    {
        if (content[i] == ' ')
            count++;
        else if (content[i] == '\n') {
            count++;
        } 
        else if (content[i + 1] == '\0') {
            count++;
        } 
    }
    return count;
}

/**
 * Frees any memory associated with the given note.
 */
void dispose(struct note *note) {
    free(note);
}
