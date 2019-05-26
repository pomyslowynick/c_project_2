#ifndef NOTE_H
#define NOTE_H

/**
 * Forward declaration of the note struct.
 */
struct note;

/**
 * Dynamically allocates a single note struct. A note comprises a title string,
 * contents string, and a priority. Copies of the title and 
 * contents strings set on the note before returning a struct note pointer.
 */
struct note* createNote(char *title, char *contents, int priority);

/**
 * Returns the priority of for the given note. The lower the integer
 * value, the higher the priority of the note.
 */
int getPriority(struct note *note);

/**
 * Returns the title of the given note. 
 */
char* getTitle(struct note *note);

/**
 * Returns the contents of the given note. 
 */
char* getContents(struct note *note);

/**
 * Returns the first line of content for the given note, i.e. all characters up
 * to but not including a line break character. 
 */
char* head(struct note *note);

/**
 * Returns the word count for the given note. Words are separated by whitespace 
 * or line-break characters; words can also by separated by punctuation characters such as period '.' 
 */
unsigned int getWordCount(struct note *note);

/**
 * Frees any memory associated with the given note.
 */
void dispose(struct note *note);

#endif