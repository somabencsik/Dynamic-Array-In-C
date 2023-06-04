#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE_INCREMENTER 3

// Example for array of int
typedef struct Array_
{
	int* array;
	int size;
	int realSize;
} Array;

Array* CreateArray(int n)
{
	Array* arr = (Array*)malloc(sizeof(Array));
	arr->array = (int*)malloc(sizeof(int) * n);
	arr->size = n;
	arr->realSize = 0;
	return arr;
}

void CheckSizeArray(Array* arr)
{
	if (arr->size == arr->realSize)
	{
		arr->array = (int*)realloc(arr->array, sizeof(int) * (arr->size + ARRAY_SIZE_INCREMENTER));
		arr->size += ARRAY_SIZE_INCREMENTER;
	}
}

void AppendArray(Array* arr, int n)
{
	CheckSizeArray(arr);	
	arr->array[arr->realSize++] = n;
}

void InsertArray(Array* arr, int n, int p)
{
	CheckSizeArray(arr);
	if (p < 0)
	{
		p = arr->size - (p * -1);
	}
	if (p > arr->realSize)
	{
		printf("You cannot insert value, the array size is smaller, than place value\n");
		return;
	}

	for (int i = arr->realSize + 1; i > p; --i)
	{
		arr->array[i] = arr->array[i - 1];
	}
	arr->array[p] = n;
	++arr->realSize;
}

void RemoveArray(Array* arr, int p)
{

	if (p < 0)
	{
		p = arr->size - (p * -1);
	}
	if (p > arr->realSize)
	{
		printf("You cannot remove value, the array size is smaller, than place value\n");
		return;
	}

	for (int i = p; i < arr->realSize - 1; ++i)
	{
		arr->array[i] = arr->array[i+1];
	}
	--arr->realSize;

	if (arr->realSize + ARRAY_SIZE_INCREMENTER == arr->size)
		arr->array = (int*)realloc(arr->array, sizeof(int) * arr->realSize);
}

void DeleteArray(Array* arr)
{
	free(arr->array);
	free(arr);
}

void PrintArray(Array* arr)
{
	for (int i = 0; i < arr->realSize; ++i)
	{
		printf("%d. %d\n", i, arr->array[i]);
	}
}

int main()
{
	Array* arr = CreateArray(5);

	for (int i = 0; i < 10; ++i)
	{
		AppendArray(arr, (10 - i));
	}

	printf("Original list:\n");
	PrintArray(arr);

	DeleteArray(arr);

	return 0;
}
