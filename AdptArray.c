#include <string.h>

#include <stdlib.h>

#include <assert.h>

#include "AdptArray.h"





struct AdptArray_{

    int capacity;

    PElement* items;

    COPY_FUNC copyFunc;

    DEL_FUNC delFunc;

    PRINT_FUNC printFunc;

}AdptArray;







PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc,PRINT_FUNC printFunc){

    PAdptArray array = (PAdptArray)malloc(sizeof(AdptArray));

    if(array == NULL) return NULL;



    array->items = (PElement*)malloc(sizeof(PElement));

    if(array->items == NULL){

        free(array);

        return NULL;

    }

    array->copyFunc = copyFunc;

    array->printFunc = printFunc;

    array->delFunc = delFunc;

    array->capacity = 1;



    int i;

    for(i = 0 ; i < array->capacity ; i++){

        array->items[i] = NULL;

    }

    return array;

}



PElement* resizeAdptArray(PAdptArray adt, int size){

    if(adt == NULL) return NULL;

    PElement *newArray = (PElement*)realloc(adt->items,size*sizeof(PElement));

    if(newArray == NULL) return NULL;

    int i;

    for(i = adt->capacity ; i < size ; i++){

        newArray[i] = NULL;

    }

    adt->capacity=size;



    return newArray;

}



void DeleteAdptArray(PAdptArray adt){

    if(adt == NULL) return;



    if(adt->items != NULL){

        int i;

        for(i = 0 ; i < adt->capacity ; i++){

            if(adt->items[i] != NULL){

                adt->delFunc(adt->items[i]);

            }

        }

        free(adt->items);

    }

    free(adt);

}

Result SetAdptArrayAt(PAdptArray adt, int index, PElement element){

    if(adt == NULL || index < 0) return FAIL;

    if(index >= adt->capacity){

        size_t newCapacity = index+1;

        PElement* newArray = resizeAdptArray(adt,newCapacity);

        if(newArray == NULL) return FAIL;

        adt->items = newArray;

    }



    if(adt->items[index] != NULL){

        adt->delFunc(adt->items[index]);

    }



    if(element != NULL) {

        adt->items[index] = adt->copyFunc(element);

    }

    return SUCCESS;

}







PElement GetAdptArrayAt(PAdptArray adt, int index) {

    if(adt == NULL || index < 0 || adt->items == NULL || index>=adt->capacity) return NULL;

  

    if(adt->items[index] == NULL) return NULL;

    return adt->copyFunc(adt->items[index]);

}







int GetAdptArraySize(PAdptArray adt) {

    if (adt == NULL) {

        return 0;

    }



    return adt->capacity;

}



void PrintDB(PAdptArray adt){

    if (adt == NULL || adt->printFunc == NULL) {

        return;

    }



    int i;

    for(i = 0 ; i < adt->capacity ; i++){

        if(adt->items[i] != NULL){

            adt->printFunc(adt->items[i]);

        }

    }

}

