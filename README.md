# CS2521A1_Test
Test file for the GADT Implementation for CS2521A1
All tests should only call functions from the listIteratorG.h file to ensure no other function dependencies.

Added a test program that lets you call functions step by step and also see the list at any step:
  Commands that it takes:
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
