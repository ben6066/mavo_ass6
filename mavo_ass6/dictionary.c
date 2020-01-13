#include "dictionary.h"
#include <stdio.h>

int isKeyInDictionary(Dictionary* d, int key);

Dictionary* initDictionary()
{
	//Allocating a dictionary struct
	Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary));

	if (dictionary == NULL)
	{
		printf("Malloc has failed in 'initDictionary'\n");
		return NULL;
	}

	dictionary->size = 0;

	dictionary->dic = (Element*)malloc(sizeof(Element));

	if (dictionary->dic == NULL)
	{
		free(dictionary);
		printf("Malloc has failed in 'initDictionary'\n");
	}

	return dictionary;
}

void destroyDictionary(Dictionary* d)
{
	if (d != NULL)
	{
		if (d->dic != NULL)
		{
			free(d->dic);
		}

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
	int inDic = -1;

	if (d->size == 0)
	{
		//Return -1 in case key isn't in dictionary
		return inDic;
	}

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
	int isKeyInDic = isKeyInDictionary(d, key);

	if (isKeyInDic != -1)
	{
		d->dic[isKeyInDic].value = value;
		return SUCEESS;
	}

	//Create var
	Element var;
	var.key = key;
	var.value = value;

	//If we insert the first var
	if (d->size == 0)
	{
		d->dic[d->size] = var;
		d->size++;
		return SUCEESS;
	}

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

	//Insertion sort
	for (int i = 0; i < d->size; i++)
	{
		if (d->dic[i].key > var.key)
		{
			d->size++;

			for (int j = d->size - 1; j > i; j--)
			{
				d->dic[j] = d->dic[j - 1];
			}

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
