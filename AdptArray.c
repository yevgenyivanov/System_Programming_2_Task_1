#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// using moed-A solutions of prequesite course - System Programming A and added PRINT_FUNC to the struct (based on the Demo.c and AdptArray.h files)

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray;




PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc_;
	return pArr;
}



Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
    if(pArr ==  NULL || pNewElem == NULL || idx<0){
        return FAIL;
    }
	PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{
		
// Extend Array
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}


	// Delete Previous Elem
    
    if( (pArr->pElemArr)[idx] != NULL){
        pArr->delFunc((pArr->pElemArr)[idx]);
    }
	
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}


void DeleteAdptArray(PAdptArray pArr)
{
	
	if (pArr == NULL)
		return;
	//check if pArr not null but pElemArr is null
	if(pArr->pElemArr == NULL){
		free(pArr);
		return;
	}
	for(int i = 0; i < pArr->ArrSize; ++i)
	{
		// remove element if it exists in pElemArr, otherwise continue
		if(pArr->pElemArr[i] != NULL)
			pArr->delFunc((pArr->pElemArr)[i]);
	}
	free(pArr->pElemArr);
	free(pArr);

}


// additional-writted functions that were not in the moed-A solutions 
int GetAdptArraySize(PAdptArray pArr){
    if(pArr == NULL ){
        return -1;
    }

    return pArr->ArrSize;
}


PElement GetAdptArrayAt(PAdptArray pArr, int idx){
    if(pArr == NULL || // if pointer of given adptarray is null
    (pArr->ArrSize) <= idx || // if the size of adptarray is less than or equal to index (can get seg-fault even if ArrSize==index)
    (pArr->pElemArr)[idx] == NULL // if the element is nonexistent at the element array 
    ){
        return NULL;
    }
    return pArr->copyFunc((pArr->pElemArr)[idx]);
}

void PrintDB(PAdptArray pArr){
    if(pArr==NULL){
        return;
    }
    for(int i=0;i<pArr->ArrSize;i++){
        if((pArr->pElemArr)[i] != NULL)
            pArr->printFunc(pArr->pElemArr[i]);
    }
}