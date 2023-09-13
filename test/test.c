#include <stdio.h>
#include <assert.h>
#include "../src/monad.h" 

void printValue(_Generic_T_ value) {
    printf("Value: %d\n", *(int*)value);
}

bool isEven(_Generic_T_ value) {
    return (*(int*)value) % 2 == 0;
}

_Generic_T_ square(_Generic_T_ value) {
    int* squared = malloc(sizeof(int));
    *squared = (*(int*)value) * (*(int*)value);
    return squared;
}

// Supplier function for testing
_Generic_T_ supplyValue() {
    int* p = malloc(sizeof(int));
    *p = 15;
    return p;
}

int main() {
    // Test optional_new()
    Optional* opt1 = optional_new();
    assert(opt1 != NULL);

    // Test optional_Of()
    int x = 5;
    Optional* opt2 = optional_Of(&x);
    assert(optional_isPresent(opt2));

    // Test optional_ofNullable()
    Optional* opt3 = optional_ofNullable(NULL);
    assert(opt3->value == NULL);
    
    // Test optional_Empty()
    Optional* opt4 = optional_Empty();
    assert(!optional_isPresent(opt4));

    // Test optional_isPresent()
    assert(optional_isPresent(opt2));
    assert(!optional_isPresent(opt4));

    // Test optional_ifPresent()
    optional_ifPresent(opt2, printValue);

    // Test optional_orElse()
    int y = 10;
    int* res1 = optional_orElse(opt2, &y);
    int* res2 = optional_orElse(opt4, &y);
    assert(*res1 == x);
    assert(*res2 == y);

    // Test optional_orElseGet()
    int* res3 = optional_orElseGet(opt4, supplyValue);
    assert(*res3 == 15);
    free(res3);  // Clean up

    // Test optional_Map()
    Optional* opt5 = optional_Map(opt2, square);
    assert(optional_isPresent(opt5));
    assert(*((int*)opt5->value) == x * x);
    free(opt5->value);  // Clean up

    // Test optional_Filter()
    Optional* opt6 = optional_Filter(optional_Of(&x), isEven);
    assert(!optional_isPresent(opt6));

    // Test optional_Free()
    optional_Free(opt1);
    optional_Free(opt2);
    optional_Free(opt3);
    optional_Free(opt4);
    optional_Free(opt5);
    optional_Free(opt6);

    printf("All tests passed!\n");
    return 0;
}
