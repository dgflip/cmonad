=================================================================================
                            OPTIONAL LIBRARY IN C
=================================================================================

DESCRIPTION:
---------------------------------------------------------------------------------
This is a "toy" library aimed at replicating the Java Optional Monad in the C 
programming language. The library provides a way to represent optional values 
that are either present or absent, without using NULL pointers. This allows for 
more expressive, safer code and alleviates some common issues associated with 
NULL pointers.

GOAL:
---------------------------------------------------------------------------------
The goal of this library is educational, to demonstrate how one might implement 
the concept of an Optional Monad in C. It is not intended for production use and 
might lack some of the features or performance optimizations found in robust 
implementations.

SHORT EXAMPLE:
---------------------------------------------------------------------------------
Here is a short example demonstrating how to use the Optional library.

#include <stdio.h>
#include "Optional.h"

void printValue(_Generic_T_ value) {
    printf("Value: %d\n", *(int*)value);
}

int main() {
    int x = 5;

    // Create an Optional from a value
    Optional* opt1 = optional_Of(&x);

    // Check if value is present and print
    if (optional_isPresent(opt1)) {
        printValue(opt1->value);
    }

    // Clean up
    optional_Free(opt1);
    
    return 0;
}

This program will output "Value: 5", as the Optional does contain a value.

For more details and usage, refer to the code and comments in 'monad.h'.

=================================================================================
