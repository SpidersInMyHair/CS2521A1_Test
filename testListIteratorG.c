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

void printIntList(IteratorG it);
void printStringList(IteratorG it);
void testSetAndDelete(IteratorG it, void *replace);

int main(int argc, char *argv[])
{
  
  /* The following code, inside the comments, may or may not be correct!
     
     It's provided in case you find it difficult to understand 
     how to create a generic list iterator, and use it's functions.
     
     Please study SetG example we discussed in the lecture in detail.

     The code below only tests basic operations, however 
     make sure that you do test all the required functions properly in
     your test file. 

  */
  
  /* =======================================
     --------- positiveIntType List Iterator ----------
  */
  

  IteratorG it1 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
  
  int a[MAXARRAY] = { 25, 12, 6, 82 , 11};

  int i;
  for(i=0; i<MAXARRAY; i++){
    int result = add(it1 , (void *)&a[i]); 
    printf("Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }

	/*
	The above loop should print ... 
		Inserting 25: Success 
		Inserting 12: Success 
		Inserting 6: Success 
		Inserting 82: Success 
		Inserting 11: Success
	*/  


  int *v1 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v1 );  // should print "Previous value is: 11" 
  
  int *v2 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v2 );  // should print "Previous value is: 82" 
  
  int *v3 = (int *) next(it1);
  printf("Next value is: %d \n", *v3 );     // should print "Next value is: 82" 

  // Own Tests Run Below //
  printf("\n");
  printIntList(it1);
  int replace = 5;
  testSetAndDelete(it1, (void *)(&replace));
  /* =======================================
     --------- stringType List Iterator ----------
  */
 

  IteratorG it2 = IteratorGNew(stringCompare, stringNew, stringFree);
  
  char *strA[MAXARRAY];
  strA[0] = strdup("John");
  strA[1] = strdup("Rita");
  strA[2] = strdup("John");
  strA[3] = strdup("Abby"); 
  
  int j;
  for(j=0; j<4; j++){
    int result = add(it2 , strA[j]); 
    printf("Inserting %s: %s \n", strA[j], (result==1 ? "Success" : "Failed") );
  }

	/*
	The above loop should print ... 
		Inserting John: Success 
		Inserting Rita: Success 
		Inserting John: Success 
		Inserting Abby: Success
	*/
 
  char *v4 = (char *) previous(it2);
  printf("Previous value is: %s \n", v4 );  // should print: "Previous value is: Abby"  

  char *v5 = (char *) previous(it2);
  printf("Previous value is: %s \n", v5 );  // should print: "Previous value is: John"

  char *v6 = (char *) next(it2);
  printf("Next value is: %s \n", v6 );      // should print: "Next value is: John"                        

  char *v7 = (char *) next(it2);            // should print: "Next value is: Abby"
  printf("Next value is: %s \n", v7);
 
  // Own Tests Run Below //
  printf("\n");
  printStringList(it2);
  testSetAndDelete(it2, (void *)"TheReplacement");

  return EXIT_SUCCESS; 
}

void printIntList(IteratorG it)
{
    printf("Resetting the cursor\n");
    reset(it);
    printf("    Successfully reset the cursor\n");
    printf("FORWARD Iterating and Printing Int list:\n");
    int fcount = 0;
    while (hasNext(it)) {
        int *n = (int *) next(it);
        fcount ++;
        printf("%d\n", *n);
    }
    printf("\n");
    printf("REVERSE Iterating and Printing Int list:\n");
    int rcount = 0;
    while (hasPrevious(it)) {
        int *p = (int *) previous(it);
        rcount ++;
        printf("%d\n", *p);
    }
    printf("\n");
    if (fcount != rcount) {
        printf("    MISMATCH BETWEEEN FORWARD AND REVERSE ITERATION");
        exit(1);
    }
}

void printStringList(IteratorG it)
{
    printf("Resetting the cursor\n");
    reset(it);
    printf("    Successfully reset the cursor\n");
    printf("FORWARD Iterating and Printing String list:\n");
    int fcount = 0;
    while (hasNext(it)) {
        char *n = (char *) next(it);
        printf("%s\n", n);
        fcount ++;
    }
    printf("\n");
    printf("REVERSE Iterating and Printing String list:\n");
    int rcount = 0;
    while (hasPrevious(it)) {
        char *p = (char *) previous(it);
        rcount ++;
        printf("%s\n", p);
    }
    printf("\n");
    if (fcount != rcount) {
        printf("    MISMATCH BETWEEEN FORWARD AND REVERSE ITERATION");
        exit(1);
    }
}

void testSetAndDelete(IteratorG it, void *replace)
{
    // List should contain at least 1 item when starting this test
    printf("Resetting the cursor\n");
    reset(it);
    printf("    Succesffully reset the cursor\n");
    // Replace/Set the first item
    // Attempt to replace without a direct precall to a neccessary function
    if (set(it, replace) != 0) printf("Test failed: Either set does not return appropriately or set executes when precondition not met\n");
    next(it);
    if (set(it, replace) != 1) printf("Test failed: Unable to set value when precondition successfully met\n");
    if (delete(it) != 0) printf("Test failed: Either delete does not return appropriately or delete executes when precondition not met\n");
    previous(it);
    if (delete(it) != 1) printf("Test failed: Unablem to delete value when precondition successfully met\n");
    printf("    Successfully ran Set and Delete tests\n");
}

