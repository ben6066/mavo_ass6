#include "dictionary.h"
#include <stdio.h>

//int isKeyInDictionary(Dictionary* d, int key, int value);

Dictionary* initDictionary()
{
	Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary));

	if (dictionary == NULL)
	{
		printf("Malloc has failed");
		return NULL;
	}

	dictionary->size = 0;

	dictionary->dic = (Element*)malloc(sizeof(Element));

	if (dictionary->dic == NULL)
	{
		free(dictionary);
		printf("Malloc has failed");
	}

	return dictionary;
}

void destroyDictionary(Dictionary* d)
{
	if (d->dic == NULL)
	{
		return;
	}

	free(d->dic);
}

int sizeOfDictionary(Dictionary* d)
{
	return d->size;
}

int isKeyInDictionary(Dictionary* d, int key, int value)
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
	int isKeyInDic = isKeyInDictionary(d, key, value);

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

	//Insertion sort
	for (int i = 0; i < d->size; i++)
	{
		if (d->dic[i].key > var.key)
		{
			Element* backup = d->dic;

			d->dic = realloc(d->dic, sizeof(Element) * (d->size + 1));

			//Case realloc failed
			if (d->dic == NULL)
			{
				//free(backup); - check with eyal
				printf("Malloc has failed");
				return MEM_ERROR;
			}

			//backup = NULL; - check with eyal

			d->size++;

			for (int j = d->size - 1; j > i; j--)
			{
				d->dic[j] = d->dic[j - 1];
			}

			d->dic[i] = var;

			return SUCEESS;
		}
	}

	Element* backup = d->dic;

	d->dic = realloc(d->dic, sizeof(Element) * (d->size + 1));

	//Case realloc failed
	if (d->dic == NULL)
	{
		//free(backup); - check with eyal
		printf("Malloc has failed");
		return MEM_ERROR;
	}

	//backup = NULL; - check with eyal

	d->size++;

	d->dic[d->size - 1] = var;

	return SUCEESS;
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
