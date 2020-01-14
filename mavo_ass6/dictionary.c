#include "dictionary.h"
#include <stdio.h>

int isKeyInDictionary(Dictionary* d, int key);

Dictionary* initDictionary()
{
	//Allocate a dictionary struct
	Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary));

	//Case malloc failed
	if (dictionary == NULL)
	{
		printf("Malloc has failed in 'initDictionary'\n");
		return NULL;
	}

	//Set default size as 0
	dictionary->size = 0;

	//Allocate Element's array
	dictionary->dic = (Element*)malloc(sizeof(Element));

	//Case malloc failed
	if (dictionary->dic == NULL)
	{
		//Free the struct allocated
		free(dictionary);
		printf("Malloc has failed in 'initDictionary'\n");
	}

	return dictionary;
}

void destroyDictionary(Dictionary* d)
{
	//Check there's something to free
	if (d != NULL)
	{
		//Check if an array of elements has been allocated
		if (d->dic != NULL)
		{
			//Free the array
			free(d->dic);
		}

		//Free the struct allocated
		free(d);
		return;
	}
}

int sizeOfDictionary(Dictionary* d)
{
	return d->size;
}

int isKeyInDictionary(Dictionary* d, int key)
{
	//Declaration of a flag with default value -1(key isn't in dictionary)
	int inDic = -1;

	//The array is empty so the key isn't in dictionary
	if (d->size == 0)
	{
		return inDic;
	}

	//Check each element's key until found or not found at all
	for (int i = 0; i < d->size && inDic == -1; i++)
	{
		if (d->dic[i].key == key)
		{
			//Return the matchig index in case key is in dictionary
			inDic = i;
		}
	}

	return inDic;
}

Result putInDictionary(Dictionary* d, int key, int value)
{
	//If key is in dictionary, isKeyInDic holds the key's index, if not it holds -1
	int isKeyInDic = isKeyInDictionary(d, key);

	//If key is in dictionary, just repalce it's value and return Sucess
	if (isKeyInDic != -1)
	{
		d->dic[isKeyInDic].value = value;
		return SUCEESS;
	}

	//Create a new element
	Element var;
	var.key = key;
	var.value = value;

	
	//Case array is empty - enter the element and promote size with 1 - return Sucess
	if (d->size == 0)
	{
		d->dic[d->size] = var;
		d->size++;
		return SUCEESS;
	}

	/*Case array isn't empty, expand the array with realloc
	  Declare a backup pointer in case realloc failes
	  Try to expand array's size by 1 (size of Element)
	*/
	Element* backup = d->dic;

	d->dic = realloc(d->dic, sizeof(Element) * (d->size + 1));

	//Case realloc failed
	if (d->dic == NULL)
	{
		//free(backup); - check with eyal
		printf("Malloc has failed\n");
		d->dic = backup;
		return MEM_ERROR;
	}

	//Insertion sort - make sure all of the elements entered to the dictionary are sorted
	for (int i = 0; i < d->size; i++)
	{
		//Case an element with a bigger key than the new element's key is found
		if (d->dic[i].key > var.key)
		{
			//Promote size with 1
			d->size++;

			//Move all of the elements from the element found 1 to the right
			for (int j = d->size - 1; j > i; j--)
			{
				d->dic[j] = d->dic[j - 1];
			}

			//Insert the new element in the place the bigger element's key is found
			d->dic[i] = var;

			return SUCEESS;
		}
	}

	d->size++;

	d->dic[d->size - 1] = var;

	return SUCEESS;
}

int getFromDictionary(Dictionary* d, int key)
{
	for (int i = 0; i < d->size; i++)
	{
		if (d->dic[i].key == key)
		{
			return d->dic[i].value;
		}
	}

	return 0;
}

void printDictionary(Dictionary* d)
{
	printf("{");

	for (int i = 0; i < d->size; i++)
	{
		printf("[%d:%d]", d->dic[i].key, d->dic[i].value);
	}

	printf("}");
}

Result removeFromDictionary(Dictionary* d, int key)
{
	int isKeyInDic = isKeyInDictionary(d, key);

	if (isKeyInDic == -1)
	{
		return FAILURE;
	}

	if (isKeyInDic == 0 && d->size == 1)
	{
		d->size = 0;
		return SUCEESS;
	}

	for (int i = isKeyInDic; i < d->size - 1; i++)
	{
		d->dic[i] = d->dic[i + 1];
	}

	Element* backup = d->dic;

	d->dic = realloc(d->dic, sizeof(Element) * (d->size - 1));

	//Case realloc failed
	if (d->dic == NULL)
	{
		//free(backup); - check with eyal
		printf("Malloc has failed\n");
		d->dic = backup;
		return MEM_ERROR;
	}

	//backup = NULL; - check with eyal

	d->size--;

	return SUCEESS;
}

Dictionary* createDictionaryFromArrays(int keys[], int values[], int size)
{
	Dictionary* pDic = initDictionary();

	if (pDic == NULL)
	{
		printf("Malloc has failed in 'createDictionaryFromArrays'\n");
		return NULL;
	}

	Element var;

	for (int i = 0; i < size; i++)
	{
		var.key = keys[i];
		var.value = values[i];

		Result r = putInDictionary(pDic, var.key, var.value);

		if (r != SUCEESS)
		{
			printf("Malloc failed\n");
			return NULL;
		}
	}

	return pDic;
}
