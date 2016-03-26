#include<stdio.h>
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
/*#include"graph.h"

nod** heap;                                                         // this id the heap that will contain every "possibly next node"
int heapSize;                                                       // this is the size of the heap
///////////////////////////////////////////////////////////////////////////////////
int                                                                 //
    compare(nod * N1, nod* N2){                                     //
    if(N1->dist < N2->dist)                                         //
        return 1;                                                   //
    return 0;                                                       //
}

///////////////////////////////////////////////////////////////////////////////////

void
    swap(int n1, int n2){
    nod * temp = heap[n1];
    heap[n1] = heap[n2];
    heap[n2] = temp;
}

///////////////////////////////////////////////////////////////////////////////////

void
    push(nod* N){
    heap[heapSize] = N;
    heapSize ++ ;
    int current = heapSize - 1;
    if(heapSize != 0)
        while(1){
            if(compare(heap[current], heap[(current - 1) / 2]))
                swap(current, (current - 1)/2);
            if(current == 0 ||
                    !compare(heap[current], heap[(current - 1) / 2]))
                break;
        }
    N->visited = 1;
}

///////////////////////////////////////////////////////////////////////////////////

nod *
    pop(){
    swap(0, heapSize-1);
    nod * max = heap[heapSize-1];
    heapSize--;
    int current = 0;
    int child;
    while(1){
        child = current * 2 + 1;
        if(child < heapSize && child + 1 >= heapSize){
            if(compare(heap[child], heap[current]))
                swap(current, child);
            break;
        }
        if(child >= heapSize || child + 1 > heapSize)
            break;
        if(compare(heap[child], heap[current]))
            swap(child, current);
        else
            break;
        current = child;
    }
    max->end = 1;
    return max;
}

///////////////////////////////////////////////////////////////////////////////////

void
    initHeap(int sizeMax) {
    heap = malloc(sizeof(nod*)*sizeMax);
    heapSize = 0;
}
*/
size_t bytes;
void** heap;                                                         // this id the heap that will contain every "possibly next node"
int heapSize;                                                       // this is the size of the heap
///////////////////////////////////////////////////////////////////////////////////
int                                                                 //
compare(void * N1, void* N2){                                     //
    if(*(int*)N1 > *(int*)N2)                                         //
        return 1;                                                   //
    return 0;                                                       //
}

///////////////////////////////////////////////////////////////////////////////////

void
swap(int n1, int n2){
    void ** temp = malloc(bytes);
    unsigned char * c_1 = (unsigned char*)(heap + n1 * bytes);
    unsigned char * c_2 = (unsigned char*)(heap + n2 * bytes);
    memcpy(temp, c_1, bytes);
    memcpy(c_1, c_2, bytes);
    memcpy(c_2, temp, bytes);
    free(temp);
}

///////////////////////////////////////////////////////////////////////////////////

void
push(void* n){
    memcpy((char*)(heap + heapSize*bytes), n, bytes);
    printf("%p, %d\n",(char*)(heap + heapSize*bytes), heapSize );
    heapSize ++ ;
    int current = heapSize - 1;
    if(heapSize != 0)
        while(1){
            if(compare(heap + current*bytes, heap + (current - 1) / 2 * bytes))
                swap(current, (current - 1)/2);
            if(current == 0 ||
               !compare(heap + current*bytes, heap + (current - 1) / 2 * bytes))
                break;
        }
}

///////////////////////////////////////////////////////////////////////////////////

void *
pop(){
    swap(0, heapSize-1);
    void* max = heap + heapSize-1 * bytes;
    heapSize--;
    int current = 0;
    int child;
    while(1){
        child = current * 2 + 1;
        if(child < heapSize && child + 1 >= heapSize){
            if(compare(heap + child*bytes, heap + current*bytes))
                swap(current, child);
            break;
        }
        if(child >= heapSize || child + 1 > heapSize)
            break;
        if(compare(heap + child*bytes, heap + current * bytes))
            swap(child, current);
        else
            break;
        current = child;
    }
    return max;
}

///////////////////////////////////////////////////////////////////////////////////

void
initHeap(int sizeMax, size_t type) {
    bytes = type;
    heap = malloc(bytes*sizeMax);
    heapSize = 0;
}

void freeHeap(){
    free(heap);
}

void display(){
    int i;
    for(i = 0 ; i < heapSize ; ++i)
        printf("%d ", *(int*)(heap + i * bytes));
    puts("");
}
int main(){
    initHeap(1024, sizeof(int));
    int a = 5;
    int b = 10;
    int c = 3;
    int d = 7;

    push((void*)&a);
    push((void*)&b);
    push((void*)&c);
    push((void*)&d);
    display();
    pop();
    pop();
    pop();
    display();

    return 0;
}