/*
  testListIteratorG.c ... client to test Generic List Iterator 
*/ 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listIteratorG.h"
#include "positiveIntType.h"
#include "stringType.h" 

#define MAXARRAY 5
#define MAXINPUT 6

int last_move = 0;
void pretest(IteratorG it);
void printList(IteratorG it);

int main(int argc, char *argv[])
{
  
  // The program will provide an interface to call
  // the functions seen in listIteratorG.h as well
  // as the arguments.

  char *user_str = malloc(sizeof(char) * MAXINPUT);
  if (user_str == NULL) {
    fprintf(stderr, "Not enough memory\n");
    exit(1);
  }
  user_str[5] = '\0';

  IteratorG it1 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
  IteratorG it0 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
  pretest(it0);

  printf("Cursor DLL Interface\n");
  printf("Type 'help' or '?' to see commands.\n\n"); 
  while (strcmp(user_str, "quit\n") != 0) {
    printf("> ");
    fgets(user_str, 6, stdin);
    if (strcmp(user_str, "help\n") == 0 || user_str[0] == '?') {
        printf("\n");
        printf("Required arguments written as $arg. '$' sign not required.\n");
        printf("Note: Does not make exceptions for bad input. Will lead to odd behaviour\n");
        printf("ONLY takes in ONE LETTERED arguments.\n");
        printf("Commands: \n");
        printf("    !           will print the list\n");
        printf("For manipulation of list:\n");
        printf("    + $value    will add that value to the list\n");
        printf("    $ $value    will set value to the list\n");
        printf("    -           will delete from the list\n");
        printf("    r           will reset the cursor of list\n");
        printf("    f           will free the list\n");
        printf("For iteration of list: \n");
        printf("    a           will query if list has prev\n");
        printf("    d           will query if list has next\n");
        printf("    n $value    will find and goto the next value given\n");
        printf("    p $value    will find and goto the prev value given\n");
        printf("    <           will move the cursor to prev\n");
        printf("    >           will move the cursor to next\n");
        printf("\n");
    }

    if (user_str[0] == '!') {
        printList(it1);
    }
    if (user_str[0] == '+') {
        int value = atoi(&user_str[2]);
        add(it1, (void *)(&value));
        last_move = 0;
    }
    if (user_str[0] == '$') {
        int value = atoi(&user_str[2]);
        set(it1, (void *)(&value));
    }
    if (user_str[0] == '-') {
        delete(it1);
        last_move = 0;
    }
    if (user_str[0] == 'r') {
        reset(it1);
        last_move = 0;
    }
    if (user_str[0] == 'f') {
        freeIt(it1);
        last_move = 0;
        it1 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
        printf("Note: free cannot be tested here.\n");
    }
    if (user_str[0] == 'a') {
        printf("Has prev: %s", hasPrevious(it1) == 1 ? "True\n" : "False\n");
        last_move = 0;
    }
    if (user_str[0] == 'd') {
        printf("Has next: %s", hasNext(it1) == 1 ? "True\n" : "False\n");
        last_move = 0;
    }
    if (user_str[0] == 'n') {
        int value = atoi(&user_str[2]);
        void *vp = findNext(it1, (void *)(&value));
        if (vp != NULL) {
	    last_move = 1;
	    printf("Find next: Found\n");
        } else {
	    last_move = 0;
            printf("Find next: Not found\n");
        }
    }
    if (user_str[0] == 'p') {
        int value = atoi(&user_str[2]);
        void *vp = findPrevious(it1, (void *)(&value));
	if (vp != NULL) {
	    last_move = -1;
	    printf("Find previous: Found\n");
        } else {
	    last_move = 0;
	    printf("Find previous: Not found\n");
	}
    }
    if (user_str[0] == '<') {
        void *tmp = previous(it1);
        if (tmp == NULL) {
            printf("Prev is NULL\n");
            last_move = 0;
        }
        else {
            printf("Prev is: %d\n", *(int *)tmp);
            last_move = -1;
        }
    }
    if (user_str[0] == '>') {
        void *tmp = next(it1);
        if (tmp == NULL) {
            printf("Next is NULL\n");
            last_move = 0;
        }
        else {  
            printf("Next is: %d\n", *(int *)tmp);
            last_move = 1;
        }
    }   
  }

  return EXIT_SUCCESS;
}

// Prints the DLL including the cursor position. Since printing the list requires use of the cursor
// and other ADT functions - more lines have been added so that the list is 'restored' to its absolute
// previous position, acting as though the list was never intefered with.
void printList(IteratorG it)
{
    assert(it != NULL);
    void *cNext = NULL;
    if (hasNext(it)) {
        cNext = next(it);
        previous(it);   
    }
    reset(it);
    while (hasNext(it)) {
        void *tmp;
        if ((tmp = next(it)) == cNext) {
            printf("^, ");
        }
        printf("%d, ", *((int *)tmp));
    }
    if (cNext == NULL) printf("^, ");
    printf("\n");
    if (cNext != NULL) {
        reset(it);
        while (next(it) != cNext) {
            // pass
        }
        previous(it);
    }
    hasNext(it);
    if (last_move == -1) {
        next(it);
        previous(it);
    }
    if (last_move == 1) {
        previous(it);
        next(it);
    }
}

// A few preliminary tests to ensure that functions required to print the list are at least 
// okay in their basic functioning.
void pretest(IteratorG it)
{
    int a = 1;
    add(it, (void *)(&a));
    if (hasNext(it) != 0 || next(it) != NULL) {
        fprintf(stderr, "Has next function or next function not working as intended.\n");
        exit(1);
    }
    if (hasPrevious(it) == 0 || previous(it) == NULL) {
        fprintf(stderr, "Has previous function or previous function not working as intended.\n");
	exit(1);
    }
    if (hasPrevious(it) != 0 || previous(it) != NULL) {
	fprintf(stderr, "Has previous function or previous function not working as intended.\n");
	exit(1);
    }
    if (hasNext(it) == 0 || next(it) == NULL) {
	fprintf(stderr, "Has next function or next function not working as intended.\n");
    }
    printf("Preliminary tests passed.\n");
}
