#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "note.h"
#include "notebook.h"

#define PASS "PASS"
#define FAIL "FAIL"

struct note** testCreateNotes();
struct notebook* testCreateNotebook();
void testGetPriorityFunction(struct note**);
void testGetTitleFunction(struct note**);
void testWordCountFunction(struct note**);
void testHeadFunction(struct note**);
void testAddNoteFunction(struct notebook*, struct note**);
void testRemoveNoteFunction(struct notebook*, struct note**);
void testClearNotesFunction(struct notebook*, struct note**);
void testGetNoteAtFunction(struct notebook*, struct note**);
void testFindByTitleFunction(struct notebook*, struct note**);
void testFindByContentsFunction(struct notebook*, struct note**);
void testSortByPriorityFunction(struct notebook*, struct note**);

int main(int argc, char** argv) {

    // basic note functionality tests
    struct note** allNotes = testCreateNotes();
    testGetPriorityFunction(allNotes);
    testGetTitleFunction(allNotes);
    testWordCountFunction(allNotes);
    testHeadFunction(allNotes);

    // notebook functionality tests
    struct notebook* notebook = testCreateNotebook();
    
    // add / remove / clear tests
    testAddNoteFunction(notebook, allNotes);
    testRemoveNoteFunction(notebook, allNotes);
    testClearNotesFunction(notebook, allNotes);

    // get tests
    testGetNoteAtFunction(notebook, allNotes);
    
    // find tests
    testFindByTitleFunction(notebook, allNotes);
    testFindByContentsFunction(notebook, allNotes);

    // sort test
    testSortByPriorityFunction(notebook, allNotes);

    dispose(allNotes[0]);
    dispose(allNotes[1]);
    dispose(allNotes[2]);
     
    free(allNotes);
    
}

void testGetPriorityFunction(struct note** notes) {
    printf("Testing priority for note A: %s\n", getPriority(notes[0]) == 5 ? PASS : FAIL);
    printf("Testing priority for note B: %s\n", getPriority(notes[1]) == 1 ? PASS : FAIL);
    printf("Testing priority for note C: %s\n", getPriority(notes[2]) == 8 ? PASS : FAIL);
}

void testGetTitleFunction(struct note** notes) {
    printf("Testing title for note A: %s\n", strcmp(getTitle(notes[0]), "Note A Title") ? FAIL : PASS);
    printf("Testing title for note B: %s\n", strcmp(getTitle(notes[1]), "Note B Title") ? FAIL : PASS);
    printf("Testing title for note C: %s\n", strcmp(getTitle(notes[2]), "Note C Title") ? FAIL : PASS);
}

void testWordCountFunction(struct note** notes) {

    int wordCountNoteA = getWordCount(notes[0]);
    printf("Testing word count for note A: %s\n", wordCountNoteA == 30 ? PASS : FAIL);

    int wordCountNoteB = getWordCount(notes[1]);
    printf("Testing word count for note B: %s\n", wordCountNoteB == 25 ? PASS : FAIL);

    int wordCountNoteC = getWordCount(notes[2]);
    printf("Testing word count for note C: %s\n", wordCountNoteC == 29 ? PASS : FAIL);

}

void testHeadFunction(struct note** notes) {

    char* noteAHead = head(notes[0]);
    printf("Testing head function for noteA: %s\n", 
        strcmp(noteAHead, "Lorem ipsum dolor sit amet, consectetur adipiscing elit.") ? FAIL : PASS);


    char* noteBHead = head(notes[1]);
    printf("Testing head function for noteB: %s\n", 
        strcmp(noteBHead, "Suspendisse convallis aliquet lorem, sed facilisis nisl faucibus tincidunt.") ? FAIL : PASS);

    char* noteCHead = head(notes[2]);
    printf("Testing head function for noteC: %s\n", 
        strcmp(noteCHead, "Aliquam a erat et urna tristique fringilla eget lobortis magna.") ? FAIL : PASS);

}

struct note** testCreateNotes() {

    struct note** notes = (struct note**) malloc (3 * sizeof(struct note*));

    notes[0] = createNote("Note A Title",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n"
        "Etiam ut ipsum ac nibh sollicitudin viverra.\n"
        "Mauris a lectus diam. Praesent eget urna eu massa sagittis rhoncus ut sit amet massa.",
        5
    );
    printf("Testing note A creation: %s\n", notes[0] == NULL ? FAIL : PASS);

    notes[1] = createNote("Note B Title",
        "Suspendisse convallis aliquet lorem, sed facilisis nisl faucibus tincidunt.\n"
        "Etiam finibus, mi hendrerit venenatis molestie, nibh lacus vulputate enim, a ultrices sem tortor vitae nisi.",
        1
    );
    printf("Testing note B creation: %s\n", notes[1] == NULL ? FAIL : PASS);

    notes[2] = createNote("Note C Title",
        "Aliquam a erat et urna tristique fringilla eget lobortis magna.\n"
        "Morbi nec libero in sapien ultrices sollicitudin ultricies sed nulla.\n"
        "Cras varius malesuada est, vel luctus magna dapibus non.",
        8
    );
    printf("Testing note C creation: %s\n", notes[2] == NULL ? FAIL : PASS);

    return notes;
}

struct notebook* testCreateNotebook() {
    struct notebook* notebook = createNotebook();
    printf("Testing notebook creation: %s\n", notebook == NULL ? FAIL : PASS);
    return notebook;
}

void testAddNoteFunction(struct notebook* notebook, struct note** notes) {
    addNote(notebook, notes[0]);
    printf("Testing notebook size after addNote: %s\n", countNotes(notebook) == 1 ? PASS : FAIL);

    addNote(notebook, notes[1]);
    printf("Testing notebook size after addNote: %s\n", countNotes(notebook) == 2 ? PASS : FAIL);

    addNote(notebook, notes[2]);
    printf("Testing notebook size after addNote: %s\n", countNotes(notebook) == 3 ? PASS : FAIL);
}


void testRemoveNoteFunction(struct notebook* notebook, struct note** notes) {
    removeNote(notebook, notes[1]);
    printf("Testing notebook size after removeNote: %s\n", countNotes(notebook) == 2 ? PASS : FAIL);

    // no longer present in notebook, should not affect size
    removeNote(notebook, notes[1]);
    printf("Testing notebook size after removeNote: %s\n", countNotes(notebook) == 2 ? PASS : FAIL);

    removeNote(notebook, notes[2]);
    printf("Testing notebook size after removeNote: %s\n", countNotes(notebook) == 1 ? PASS : FAIL);

    removeNote(notebook, notes[0]);
    printf("Testing notebook size after removeNote: %s\n", countNotes(notebook) == 0 ? PASS : FAIL);
}

void testClearNotesFunction(struct notebook* notebook, struct note** notes) {    
    //add notes
    addNote(notebook, notes[0]);
    addNote(notebook, notes[1]);
    addNote(notebook, notes[2]);

    clearNotes(notebook);
    int size = countNotes(notebook);
    printf("Testing clearNotes: %s\n", size == 0 ? PASS : FAIL);
}

void testGetNoteAtFunction(struct notebook* notebook, struct note** notes) {

     //add notes
    addNote(notebook, notes[0]);
    addNote(notebook, notes[1]);
    addNote(notebook, notes[2]);
    addNote(notebook, notes[0]);
    addNote(notebook, notes[1]);
    addNote(notebook, notes[2]);

    struct note* matchingNote = getNoteAt(notebook, 0);
    printf("Testing getNoteAt(0): %s\n", matchingNote == notes[0] ? PASS : FAIL);

    matchingNote = getNoteAt(notebook, 2);
    printf("Testing getNoteAt(2): %s\n", matchingNote == notes[2] ? PASS : FAIL);
    
    matchingNote = getNoteAt(notebook, 3);
    printf("Testing getNoteAt(4): %s\n", matchingNote == notes[0] ? PASS : FAIL);
    
    matchingNote = getNoteAt(notebook, 10);
    printf("Testing getNoteAt(10): %s\n", matchingNote ? FAIL : PASS);

    clearNotes(notebook);

} 

void testFindByTitleFunction(struct notebook* notebook, struct note** notes) {
    //add notes
    addNote(notebook, notes[0]);
    addNote(notebook, notes[1]);
    addNote(notebook, notes[2]);

    struct note* matchingNote = findByTitle(notebook, "Note C Title");
    printf("Testing findByTitle (title exists): %s\n", matchingNote == notes[2] ? PASS : FAIL);
    
    matchingNote = findByTitle(notebook, "No such title");
    printf("Testing findByTitle (title does not exist): %s\n", matchingNote ? FAIL : PASS);

    clearNotes(notebook);
}

void testFindByContentsFunction(struct notebook* notebook, struct note** notes) {
    //add notes
    addNote(notebook, notes[0]);
    addNote(notebook, notes[1]);
    addNote(notebook, notes[2]);

    struct note* matchingNote = findByContent(notebook, "tristique");
    printf("Testing findByContent (content exists): %s\n", matchingNote == notes[2] ? PASS : FAIL);
    
    matchingNote = findByContent(notebook, "No such content!");
    printf("Testing findByContent (content does not exist): %s\n", matchingNote ? FAIL : PASS);

    clearNotes(notebook);
}

void testSortByPriorityFunction(struct notebook* notebook, struct note** notes) {
    //add notes
    addNote(notebook, notes[0]);
    addNote(notebook, notes[1]);
    addNote(notebook, notes[2]);

    sortByPriority(notebook);

    struct note* matchingNote = getNoteAt(notebook, 0);
    printf("Testing post-sort getNoteAt(0): %s\n", matchingNote == notes[1] ? PASS : FAIL);

    matchingNote = getNoteAt(notebook, 1);
    printf("Testing post-sort getNoteAt(1): %s\n", matchingNote == notes[0] ? PASS : FAIL);
    
    matchingNote = getNoteAt(notebook, 2);
    printf("Testing post-sort getNoteAt(2): %s\n", matchingNote == notes[2] ? PASS : FAIL);
    

}


