#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

#define INITIAL_CAPACITY 1




// define functions pointers
typedef PElement (*my_copy) (PElement original);
typedef void (*my_delete) (PElement original);
typedef void (*my_print) (PElement original);

// overide the struct
typedef struct AdptArray_{
    my_copy copy; // pointer to copy function
    my_delete delete; // pointer to delete function
    my_print print; // pointer to print function

    void** data; // array of void pointers
    int used_size;    // number of elements currently in array
    int total_size; // maximum number of elements the array can hold
} *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC c, DEL_FUNC d,PRINT_FUNC p){
    //defaults
    PAdptArray list = (PAdptArray) malloc(sizeof(struct AdptArray_));
    list->used_size = 0;
    list->total_size = INITIAL_CAPACITY;
    list->data = (PElement) malloc(sizeof (PElement) * INITIAL_CAPACITY);
    // accepted
    list->copy = c;
    list->delete = d;
    list->print = p;
    return list;
}

void DeleteAdptArray(PAdptArray list){
//    for (size_t i = 0; i <= list->used_size; i++)
//    {
//        if(list->data[i])
//        {
//            list->delete(list->data[i]);
//        }
//    }
//    free(list->copy);
//    free(list->print);
//    free(list->delete);
    free(list->data);
    free(list);
}
Result SetAdptArrayAt(PAdptArray list, int key, PElement val)
{
    if(key < 0) return FAIL;
    else if(key >= list->total_size){
        int extend_size = key - list->total_size + 1; // how much to extend
        int new_total_size = list->total_size + extend_size;
        void** new_data = malloc(sizeof(void*) * new_total_size); // realloc the array
        if (new_data == NULL) {
            printf("Error: out of memory\n");
            return FAIL;
        }
        memcpy(new_data, list->data, sizeof(void*) * list->used_size);
        free(list->data);
        list->data = new_data;
        list->total_size = new_total_size;
    }

    list->data[key] = val;
    if (key > list->used_size){
        list->used_size = key + 1;
    }
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray list, int key){
    if(key<0 || key > list->used_size)
    {
        perror("key error");
        exit(1);
    }
    return list->data[key] ? list->copy(list->data[key]) : NULL;
}

int GetAdptArraySize(PAdptArray list){
    return list->used_size;
}

void PrintDB(PAdptArray list){
    for (size_t i = 0; i < list->used_size; i++)
    {
        if(list->data[i]){
            list->print(list->data[i]);
        }
    }
}