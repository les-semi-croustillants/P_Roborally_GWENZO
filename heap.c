/*#include<stdio.h>
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "array.h"
*/

#include "heap.h"
/*
typedef struct _nod{
    int dist;
    int value;
    struct _nod * next;
}nod;*/
// this id the heap that will contain every "possibly next node" // this is the size of the heap
///////////////////////////////////////////////////////////////////////////////////
int                                                                 //
comp(void * N1, void* N2){                                     //
    if(*(int*)N1 < *(int*)N2)                                         //
        return 1;                                                   //
    return 0;                                                       //
}

int (*compare)(void*, void*);

void display(dyntab* tab) {
    int i = 0;
    int i2;
    int j = 0;
    int nb_spaces = 0;
    printf("{ ");
    for (i; i < tab->size; ++i) {
        printf("%d ", *(int *) (tab->data + i * tab->bytes));
        if (i == j) {
            j = 2 *i + 2;
            puts("");
        }
    }
/*
    if(i != 0)
        nb_spaces = 4*width/((2*(i) + 2) - (2*(i - 1) +2));
    else
        nb_spaces = width*2;
    for(i2 = 0 ; i2 < nb_spaces ; ++i2){
        printf(" ");
    }*/
    puts("}");
}

///////////////////////////////////////////////////////////////////////////////////

static void
swap(int n1, int n2, dyntab * tab){
    void ** temp = malloc(tab->bytes);
    unsigned char * c_1 = (unsigned char*)(tab->data + n1 * tab->bytes);
    unsigned char * c_2 = (unsigned char*)(tab->data + n2 * tab->bytes);
    memmove(temp, c_1, tab->bytes);
    memmove(c_1, c_2, tab->bytes);
    memmove(c_2, temp, tab->bytes);
    free(temp);
}

///////////////////////////////////////////////////////////////////////////////////

void
push(void* n, dyntab* tab) {
    dyntab_push(tab, n);
    //heapSize++;
    //int current = heapSize - 1;
    int current = tab->size - 1;
    if (tab->size != 0)
        while (1) {
            if (current == 0 ||
                !compare(tab->data + current * tab->bytes, tab->data + (((current - 1) / 2) * tab->bytes)))
                break;
            if (compare(tab->data + current * tab->bytes, tab->data + (((current - 1) / 2) * tab->bytes)))
                swap(current, (current - 1) / 2, tab);
            current = (current - 1) / 2;
        }
}

///////////////////////////////////////////////////////////////////////////////////

void *
    pop(dyntab* tab){
    swap(0, tab->size -1, tab);

    void* max = tab->data + (tab->size -1) * tab->bytes;
    dyntab_pop(tab);
    //heapSize--;
    int current = 0;
    int child;
    while(1){
        child = current * 2 + 1;
        if(child < tab->size){
            if(child + 1 <  tab->size)
                if(compare(tab->data + (child + 1)*tab->bytes, tab->data + child * tab->bytes ))
                    child ++;
            if(compare(tab->data + child * tab->bytes, tab->data + current * tab->bytes))
                swap(child, current, tab);
        }
        else
            break;
        current = child;
    }

    return max;
}

///////////////////////////////////////////////////////////////////////////////////

dyntab*
initHeap(int function, size_t type) {
    compare = function;
    dyntab *tab = malloc(sizeof(dyntab));
    dyntab_init(tab, type);
    return tab;
}

void freeHeap(dyntab* tab){
    dyntab_destroy(tab);
}

int correct(dyntab* tab){
    int i;
    for(i = tab->size - 1 ; i > 0 ; -- i)
        if (compare(tab->data + i*tab->bytes, tab->data  + ((i - 1) / 2)* tab->bytes))
            return 0;
    return 1;
}
/*
int compnod(nod** n1, nod ** n2){
    if((*n1)->dist < (*n2)->dist)
        return 1;
    return 0;
}

int main(){
    dyntab* tab = initHeap(comp, sizeof(int*));
    int value = 43;
    dyntab_push(tab, &value);
    for(int i = 0 ; i < 1000; ++i){
        value = (rand()%1000) + 1;
        push(&value, tab);
    }
    if (correct(tab))
        puts("YEAHHHHHHH!!");
    else
        puts("NOOOOOOOOOO!");
    display(tab);


    return 0;
}

/*
int main(){
    nod *** space = malloc(sizeof(nod**)*1024);
    initHeap(compnod,space, 1024, sizeof(nod**));
    printf("capacity : %d\n", capacity);

    int i;
    int k;


    nod* A = malloc(sizeof(nod));
    A->dist = 50;
    A->value = 17;
    printf("yoh %p\n",A);;

    nod * B = malloc(sizeof(nod));
    B->dist = 0;
    B->value = 29;
    B->next = NULL;
    printf("yoh %p\n",B);

    A->next = B;
    correct();

    push(&A);
    push(&B);


    nod * tmp = *(nod**)pop();
    printf("%d\n",tmp->value);
    printf("%p\n",tmp);
    //printf("%d\n",((nod*)pop())->value);
    return 0;
}


*/
