#ifndef __DICTIONARY_H
#define __DICTIONARY_H

typedef enum {
    SUCEESS, FAILURE, MEM_ERROR
} Result;

typedef struct
{
	int key;
	int value;
} Element;

typedef struct
{
	Element* dic;
	int size;
} Dictionary;

Dictionary* initDictionary();
void destroyDictionary(Dictionary* d);

int sizeOfDictionary(Dictionary* d);
Result putInDictionary(Dictionary* d, int key, int value);
//int getFromDictionary(Dictionary* d, int key);
//Result removeFromDictionary(Dictionary* d, int key);

void printDictionary(Dictionary* d);

//Dictionary* createDictionaryFromArrays(int keys[], int values[], int size);

#endif
