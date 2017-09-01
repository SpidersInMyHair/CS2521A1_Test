# CS2521A1_Test
Test file for the GADT Implementation for CS2521A1 <br />
All tests should only call functions from the listIteratorG.h file to ensure no other function dependencies.<br />

Added a test program that lets you call functions step by step and also see the list at any step:<br />
  Commands that it takes:<br />
        printf("\n");<br />
        printf("Required arguments written as $arg. '$' sign not required.\n");<br />
        printf("Note: Does not make exceptions for bad input. Will lead to odd behaviour\n");<br />
        printf("Note: Last examined value reset after printing list\n");<br />
        printf("ONLY takes in ONE LETTERED arguments.\n");<br />
        printf("Commands: \n");<br />
        printf("    !           will print the list\n");<br />
        printf("For manipulation of list:\n");<br />
        printf("    + $value    will add that value to the list\n");<br />
        printf("    $ $value    will set value to the list\n");<br />
        printf("    -           will delete from the list\n");<br />
        printf("    r           will reset the cursor of list\n");<br />
        printf("    f           will free the list\n");<br />
        printf("For iteration of list: \n");<br />
        printf("    a           will query if list has prev\n");<br />
        printf("    d           will query if list has next\n");<br />
        printf("    n $value    will find and goto the next value given\n");<br />
        printf("    p $value    will find and goto the prev value given\n");<br />
        printf("    <           will move the cursor to prev\n");<br />
        printf("    >           will move the cursor to next\n");<br />
        printf("\n");<br />
