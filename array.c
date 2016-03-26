
#include "array.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

/*** Construction, destruction, allocation ***/

/* Initialization, provide element sizeof */
void dyntab_init(dyntab* tab, size_t bytes)
{
    tab->bytes = bytes ;
    tab->data = malloc(bytes) ;
    tab->size = 0 ;
    tab->capacity = 1 ;
}

/* Destruction */
void dyntab_destroy(dyntab* tab)
{
    free(tab->data) ;
    /* only for student security */
    tab->data = NULL ;
    tab->capacity = 0 ;
    tab->size = 0 ;
    tab->bytes = 0 ;
}

/* Increases / decreases capacity AND sets size */
void dyntab_resize(dyntab* tab, size_t new_size) {
    size_t new_s = new_size < 1 ? 1 : new_size ;
    void* tmp = realloc(tab->data, tab->bytes * new_s) ;
    assert(tmp && "dyntab : unable to resize array") ;
    tab->data = tmp ;
    tab->size = new_size ;
    tab->capacity = new_s ;
}

/* Increases / decreases capacity WITHOUT changing size */
void dyntab_reserve(dyntab* tab, size_t new_capacity)
{
    size_t new_c = new_capacity < tab->size ? tab->size : new_capacity ;
    new_c = new_c < 1 ? 1 : new_c ;
    void* tmp = realloc(tab->data, tab->bytes * new_c) ;
    assert(tmp && "dyntab : unable to resize array") ;
    tab->data = tmp ;
    tab->capacity = new_c ;
}

/*** Manipulation ***/

/* Set an element (index must be lower than size) */
void dyntab_set(dyntab* tab, size_t index, const void* value)
{
    assert(index < tab->size && "dyntab : out of bounds write") ;
    memcpy(tab->data + index * tab->bytes, value, tab->bytes) ;
}

/* Get an element (index must be lower than size) */
void dyntab_get(const dyntab* tab, size_t index, void* dest)
{
    assert(index < tab->size && "dyntab : out of bounds read") ;
    memcpy(dest, tab->data + index * tab->bytes, tab->bytes) ;
}

/* Add an element at the end of the array */
void dyntab_push(dyntab* tab, const void* value)
{
    if(tab->size == tab->capacity)
    {
        dyntab_reserve(tab, 2*tab->capacity) ;
    }
    memcpy(tab->data + tab->size * tab->bytes, value, tab->bytes) ;
    ++tab->size;
}

/* Remove an element at the end of the array */
void dyntab_pop(dyntab* tab)
{
    if(tab->size > 0)
    {
        --tab->size ;
    }
}

/* Remove an element at the end and copies it to dest */
void dyntab_pop_get(dyntab* tab, void* dest)
{
    assert(tab->size && "dyntab : unable to pop from empty array") ;
    --tab->size ;
    memcpy(dest, tab->data + tab->size * tab->bytes, tab->bytes) ;
}

/*** Display ***/

void dyntab_print(const dyntab* tab, void (*elem_print)(const void* elem))
{
    printf("[ ") ;
    for(size_t i = 0; i < tab->size; ++i)
    {
        elem_print(tab->data + i * tab->bytes) ;
        printf(" ") ;
    }
    printf("]\n") ;
}