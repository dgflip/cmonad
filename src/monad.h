/*
    Header only implementation of Java Optional Monad in C
*/

#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <stdbool.h>
#include <stdlib.h>

typedef void* _Generic_T_;

/* Consumer<T> takes an argument of type T and returns void. */
typedef void (*Consumer)(_Generic_T_);

/* Predicate<T> takes an argument of type T and returns a bool. */
typedef bool (*Predicate)(_Generic_T_);

/* Function<T, R> takes an argument of type T and returns a result of type R. */
typedef void* (*Function)(_Generic_T_);

/* Supplier<T> takes no arguments and returns a result of type T. */
typedef void* (*Supplier)();

typedef struct Optional {
    _Generic_T_ value;
    bool present;
} Optional;

/* Dynamic memory allocation for Optional */
Optional* optional_new() {
    return (Optional*)malloc(sizeof(Optional));
}

/* of(T value): Returns an Optional containing the given non-null value. */
Optional* optional_Of(_Generic_T_ value) {
    Optional* opt = optional_new();
    opt->value = value;
    opt->present = true;
    return opt;
}

/* ofNullable(T value): Returns an Optional containing the given value, which can be null. */
Optional* optional_ofNullable(_Generic_T_ value) {
    Optional* opt = optional_new();
    opt->value = value;
    /* Hacky: as we are using void* as a Generic T, we can't determine whether it is present because 0 is null in C. */
    opt->present = true;
    return opt;
}

/* empty(): Returns an empty Optional object. */
Optional* optional_Empty() {
    Optional* opt = optional_new();
    opt->value = NULL;
    opt->present = false;
    return opt;
}

/* isPresent(): Returns true if the Optional contains a value, false otherwise. */
bool optional_isPresent(Optional* opt) {
    return opt->present;
}

/* ifPresent(Consumer<? super T> action): Executes the given Consumer with the value if present. */
void optional_ifPresent(Optional* opt, Consumer action) {
    if (optional_isPresent(opt)) {
        action(opt->value);
    }
}

/* orElse(T other): Returns the value if present, otherwise returns other. */
_Generic_T_ optional_orElse(Optional* opt, _Generic_T_ other) {
    return optional_isPresent(opt) ? opt->value : other;
}

/* orElseGet(Supplier<? extends T> other): Returns the value if present;
   otherwise, it returns the result produced by the supplier function. 
*/
_Generic_T_ optional_orElseGet(Optional* opt, Supplier other) {
    return optional_isPresent(opt) ? opt->value : other();
}

/* map(Function<? super T, ? extends U> mapper): Transforms the value inside the Optional using a Function.
   If the Optional is empty, it remains empty.
*/
Optional* optional_Map(Optional* opt, Function mapper) {
    if (optional_isPresent(opt)) {
        return optional_Of(mapper(opt->value));
    }
    return opt;
}

/* filter(Predicate<? super T> predicate): Filters the value inside the Optional using a Predicate.
   If the Optional is empty or the predicate returns false, the result is an empty Optional.
*/
Optional* optional_Filter(Optional* opt, Predicate pred) {
    if (opt->present && !pred(opt->value)) {
        opt->present = false;
        opt->value = NULL;
    }
    return opt;
}

/* Free dynamically allocated Optional */
void optional_Free(Optional* opt) {
    if (opt) { 
        free(opt);
        opt = 0;
    }
}

#endif  // OPTIONAL_H
