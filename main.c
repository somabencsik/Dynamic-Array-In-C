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

Array CreateArray(int n)
{
	Array arr;
	arr.array = (int*)malloc(sizeof(int) * n);
	arr.size = n;
	arr.realSize = 0;
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

Array InsertArray(Array* arr, int n, int p)
{
	CheckSizeArray(arr);
	if (p < 0)
	{
		p = arr->size - (p * -1);
	}
	if (p > arr->realSize)
	{
		printf("You cannot insert value, the array size is smaller, than place value\n");
		return *arr;
	}

	Array new = CreateArray(arr->realSize + 1);
	for (int i = 0; i < p; ++i)
	{
		AppendArray(&new, arr->array[i]);
	}
	AppendArray(&new, n);
	for (int i = new.realSize-1; i < arr->realSize; ++i)
	{
		AppendArray(&new, arr->array[i]);
	}
	free(arr->array);
	return new;
}

Array RemoveArray(Array* arr, int p)
{

	Array new = CreateArray(arr->realSize - 1);
	
	if (p < 0)
	{
		p = arr->size - (p * -1);
	}
	if (p > arr->realSize)
	{
		printf("You cannot remove value, the array size is smaller, than place value\n");
		return *arr;
	}
	
	for (int i = 0; i < arr->realSize; ++i)
	{
		if (i == p) continue;
		AppendArray(&new, arr->array[i]);
	}
	free(arr->array);
	return new;
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
	Array arr = CreateArray(5);

	for (int i = 0; i < 10; ++i)
	{
		AppendArray(&arr, (10 - i));
	}

	printf("Original list:\n");
	PrintArray(&arr);

	arr = InsertArray(&arr, 3, -1);
	arr = InsertArray(&arr, 3, 22);
	arr = RemoveArray(&arr, 4);
	arr = RemoveArray(&arr, 22);

	printf("\nNew List:\n");
	PrintArray(&arr);

	return 0;
}
