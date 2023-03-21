#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"
#include "book.h"
#include "Person.h"


struct AdptArray_{

int size;
PElement* arr;
DEL_FUNC del;
PRINT_FUNC print;
COPY_FUNC copy;

};

PAdptArray CreateAdptArray(COPY_FUNC c, DEL_FUNC d,PRINT_FUNC p){

PAdptArray res = (PAdptArray)malloc(sizeof( struct AdptArray_));

if(res == NULL) return NULL;

res -> size = 0;
res -> copy = c;
res -> del = d;
res -> print = p;
res -> arr = NULL;

return res;

}

void DeleteAdptArray(PAdptArray p_arr){
if(p_arr == NULL){
        return;
  }
 for (size_t i = 0; i < p_arr->size; i++)
    {
        if (p_arr->arr[i] != NULL)
        {
            p_arr->del(p_arr->arr[i]);
        }
    
    }
 free(p_arr->arr);
 free(p_arr);
    
}

Result SetAdptArrayAt(PAdptArray p_arr, int index, PElement newElement){

    if (p_arr == NULL) 
	{
		return FAIL;
	}
PElement* newpElemArr;
    if (index >= p_arr->size)
	    {
		if ((newpElemArr = (PElement*)calloc((index + 1), sizeof(PElement))) == NULL) 
		{
			return FAIL;
		}
		memcpy(newpElemArr, p_arr->arr, (p_arr->size) * sizeof(PElement));
		free(p_arr->arr);
		p_arr->arr = newpElemArr;
        p_arr->size = index + 1;
	    }

if (p_arr->arr[index] != NULL) 
	{
		p_arr->del((p_arr->arr)[index]);
	}
p_arr->arr[index] = p_arr->copy(newElement);
	
return SUCCESS;

}

PElement GetAdptArrayAt(PAdptArray p_arr, int index){
if (index < 0 ||p_arr == NULL ||index > p_arr->size)
{
    return NULL;
}
if (p_arr->arr[index] == NULL)
{
    return NULL;
}

return p_arr->copy(p_arr->arr[index]);

}

int GetAdptArraySize(PAdptArray p_arr){
    if (p_arr == NULL)
    {
        return -1;
    }
    if (p_arr->size == 0 && p_arr->arr[0] == NULL){
        return 0;
    }
    return p_arr->size;
    
}

void PrintDB(PAdptArray p_arr){
if (!p_arr)
{
    return;
}

for (size_t i = 0; i < p_arr->size; i++)
{
    if (!p_arr->arr[i])
    {
        continue;
    }
    p_arr->print(p_arr->arr[i]);
}

}







