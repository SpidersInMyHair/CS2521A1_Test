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
void testAddAndDelete(IteratorG it, void *newValue);
void testAdd(IteratorG it, void *newValues[], int length);

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
  testAddAndDelete(it1, (void *)(&replace));
  int iList[5] = {4,3,5,1,-1};
  void *piList[5] = {&iList[0],&iList[1],&iList[2],&iList[3],&iList[4]};
  testAdd(it1, piList, 5);
  printf("\n");

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
  testAddAndDelete(it2, (void *)"MoreTests");
  char *sList[5] = {"Jack", "Jill", "Tommy", "Chuckie", "Chloe"};
  void *psList[5] = {&sList[0],&sList[1],&sList[2],&sList[3],&sList[4]};
  testAdd(it2, psList, 5);
  printf("\n");

  return EXIT_SUCCESS; 
}

// Prints the list both forwards and backwards (int type)
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

// Prints the list both forwards and backwards (string type)
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

// List should contain at least 1 item when starting this test
// Tests appropriate calls to delete and set as well as the functionality of delete and set
void testSetAndDelete(IteratorG it, void *replace)
{
    printf("Resetting the cursor\n");
    reset(it);
    printf("    Succesffully reset the cursor\n");
    // Replace/Set the first item
    // Attempt to replace without a direct precall to a neccessary function
    if (set(it, replace) != 0) {
        printf("    Test FAILED: Either set does not return appropriately or set executes when precondition not met\n");
        exit(1);
    }
    next(it);
    if (set(it, replace) != 1) {
        printf("    Test FAILED: Unable to set value when precondition successfully met\n");
        exit(1);
    }
    if (delete(it) != 0) {
        printf("    Test FAILED: Either delete does not return appropriately or delete executes when precondition not met\n");
        exit(1);
    }
    previous(it);
    if (delete(it) != 1) {
        printf("    Test FAILED: Unablem to delete value when precondition successfully met\n");
        exit(1);
    }
    printf("    Successfully ran Set and Delete tests\n");
}

// Deletes all items and attempts other breaks
// Also tests add functions
void testAddAndDelete(IteratorG it, void *newValue)
{
    printf("Resetting the cursor\n");
    reset(it);
    printf("    Successfully reset the cursor\n");
    // Delete all items in the list from first onwards
    printf("Deleting all items in list from first onwards\n");
    while (hasNext(it)) {
        next(it);
        delete(it);   
    }
    printf("    Successfully deleted all items in the list\n");
    // Attempt to delete from an empty list
    printf("Attempting to delete from an empty list\n");
    next(it);
    delete(it);
    previous(it);
    delete(it);
    printf("    Successfully avoided break on empty list delete call\n");
    // Insert a few items
    printf("Inserting three items into empty list\n");
    for (int i = 0; i < 3; i++) add(it, newValue);
    printf("    Successfully inserted into an empty list\n");
    if (hasNext(it) != 0) {
        printf("    Test FAILED: Cursor has not been set correctly after either add or delete\n");
        exit(1);   
    }
    printf("Deleting all items in the list from last backwards\n");
    while (hasPrevious(it)) {
        previous(it);
        delete(it);
    }
    printf("    Successfully ran Add and Delete tests\n");
}

// Tests add function at boundaries and average sitatuions
// Should be given a valid empty list
void testAdd(IteratorG it, void *newValues[], int length)
{
    if (length < 5) {
        printf("Provide a bigger array for newValues\n");
        exit(1);
    }
    // Add to an empty list
    printf("Adding a few elements to an empty list\n");
    add(it, newValues[0]);
    add(it, newValues[1]);
    add(it, newValues[2]);
    printf("    Successfully added a few items to empty list\n");
    reset(it);
    printf("Adding to the front of moderate sized list\n");
    add(it, newValues[3]);
    printf("    Succesffully added to front of moderate list\n");
    printf("Adding to the back of moderate sized list\n");
    while (hasNext(it)) {
        next(it);
    }
    add(it, newValues[4]);
    printf("    Succesfully added to back of moderate list\n");
    previous(it);
    previous(it);
    printf("Adding multiple items to middle of list\n");
    for (int i = 0; i < length; i++) {
        add(it, newValues[i]);
    }
    printf("    Succesfully added multiple items to middle of list\n");
}
