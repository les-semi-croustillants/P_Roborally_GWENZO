
#ifndef LIF9_DYNTAB_H
#define LIF9_DYNTAB_H

#include <stddef.h>

/*** Dynamic array type ***/

typedef struct dyntab_ {
    unsigned char* data ; /* storage */

    size_t bytes ; /* sizeof for the elements stored */
    size_t size ; /* number of elements (not bytes) */
    size_t capacity ; /* capacity for new elements (not bytes) */
} dyntab ;

/*** Construction, destruction, allocation ***/

/* Initialization, provide element sizeof */
void dyntab_init(dyntab* tab, size_t bytes) ;

/* Destruction */
void dyntab_destroy(dyntab* tab) ;

/* Increases / decreases capacity AND sets size */
void dyntab_resize(dyntab* tab, size_t new_size) ;

/* Increases /decreases capacity WITHOUT changing size */
void dyntab_reserve(dyntab* tab, size_t new_capacity) ;

/*** Manipulation ***/

/* Set an element (index must be lower than size) */
void dyntab_set(dyntab* tab, size_t index, const void* value) ;

/* Get an element (index must be lower than size) */
void dyntab_get(const dyntab* tab, size_t index, void* dest) ;

/* Add an element at the end of the array */
void dyntab_push(dyntab* tab, const void* value) ;

/* Remove an element at the end of the array */
void dyntab_pop(dyntab* tab) ;

/* Remove an element at the end and copies it to dest */
void dyntab_pop_get(dyntab* tab, void* dest) ;

/*** Display ***/

/* Prints all the elements using the provided function */
void dyntab_print(const dyntab* tab, void (*elem_print)(const void* elem)) ;

void* dyntab_return(const dyntab* tab, int cursor, int size);

#endif