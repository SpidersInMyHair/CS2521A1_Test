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

  while (strcmp(user_str, "quit\n") != 0) {
    printf("> ");
    fgets(user_str, 6, stdin);
    if (strcmp(user_str, "help\n") == 0) {
        printf("\n");
        printf("Required arguments written as $arg. '$' sign not required.\n");
        printf("Note: Does not make exceptions for bad input. Will lead to odd behaviour\n");
        printf("Note: Last examined value reset after printing list\n");
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
    }
    if (user_str[0] == '$') {
        int value = atoi(&user_str[2]);
        set(it1, (void *)(&value));
    }
    if (user_str[0] == '-') {
        delete(it1);
    }
    if (user_str[0] == 'r') {
        reset(it1);
    }
    if (user_str[0] == 'f') {
        freeIt(it1);
    }
    if (user_str[0] == 'a') {
        printf("Has prev: %s", hasPrevious(it1) == 1 ? "True\n" : "False\n");
    }
    if (user_str[0] == 'd') {
        printf("Has next: %s", hasNext(it1) == 1 ? "True\n" : "False\n");
    }
    if (user_str[0] == 'n') {
        int value = atoi(&user_str[2]);
        printf("Find next: %s", findNext(it1, (void *)(&value)) != NULL ? "Found\n" : "Not found\n");
    }
    if (user_str[0] == 'p') {
        int value = atoi(&user_str[2]);
        printf("Find prev: %s", findPrevious(it1, (void *)(&value)) != NULL ? "Found\n" : "Not found\n");
    }
    if (user_str[0] == '<') {
        void *tmp = previous(it1);
        if (tmp == NULL) {
            printf("Prev is NULL\n");
        }
        else printf("Prev is: %d\n", *(int *)tmp);
    }
    if (user_str[0] == '>') {
        void *tmp = next(it1);
        if (tmp == NULL) {
            printf("Next is NULL\n");
        }
        else printf("Next is: %d\n", *(int *)tmp);
    }   
  }

  return EXIT_SUCCESS;
}

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
}
