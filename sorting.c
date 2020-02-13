/**
 * Chris Nutter
 * Austin Kim
 * sorting.c -- a threaded array sorting program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int list[] = { 7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8 };
#define SIZE (sizeof(list) / sizeof(*list))
#define HALF (SIZE / 2)
#define NUM_THREADS 3

int result[SIZE] = {0};

typedef unsigned int uint;

typedef struct
{
	int * array;
	uint size;
} Array;

typedef struct
{
	Array left;
	Array right;
} Pair;

void * threaded_sort(void *);
void * arraymerge(void *);

void printlist(int *);
void printarray(Array *);
void swap(int *, int *);

int main()
{
	pthread_t workers[NUM_THREADS];	// sorter, sorter, merger
	pthread_attr_t attrs[NUM_THREADS];
	Array a, b;
	Pair pair; 

	a.array = list;
	a.size = HALF;

	b.array = list + HALF;
	b.size = SIZE - HALF;
	
	printf("Original: ");
	printlist(list);

	pthread_attr_init(attrs);
	pthread_create(workers, attrs, threaded_sort, &a);

	pthread_attr_init(attrs + 1);
	pthread_create(workers + 1, attrs + 1, threaded_sort, &b);

	// wait for the sorting threads
	for (int i = 0; i < NUM_THREADS - 1; i++)
	{
		pthread_join(workers[i], NULL);
	}
	
	pair.left = a;
	pair.right = b;

	pthread_attr_init(attrs + 2);
	pthread_create(workers + 2, attrs + 2, arraymerge, &pair);
	pthread_join(workers[2], NULL);

	printf("Sorted:   ");
	printlist(result);

	return 0;
}
/**
 * @param arg Array struct
 */
void * threaded_sort(void * arg)
{
	Array * arr = (Array*) arg;
	int * nums = arr->array;
	for (uint i = 1; i < arr->size; i++)
	{
		for (int j = i; j > 0 && nums[j-1] > nums[j]; j--)
		{
			swap(&nums[j-1], &nums[j]);
		}
	}

	pthread_exit(0);
}

/**
 * @param arg Pair struct
 */
void * arraymerge(void * arg)
{
	Pair * pair = (Pair*)arg;
	Array * left = &(pair->left);
	Array * right = &(pair->right);
	uint i = 0, j = 0, n = 0;

	while (n < SIZE && i < left->size && j < right->size)
	{
		if (left->array[i] < right->array[j])
		{
			result[n] = left->array[i];
			i++;
		}
		else
		{
			result[n] = right->array[j];
			j++;
		}
		n++;
	}

	if (i < left->size)
	{
		uint leftover = left->size - i;
		memcpy(result + n, left->array + i, sizeof(int) * leftover);
	}
	else if (j < right->size)
	{
		uint leftover = right->size - j;
		memcpy(result + n, right->array + j, sizeof(int) * leftover);
	}

	pthread_exit(0);
}

void printlist(int * nums)
{
	for (uint i = 0; i < SIZE; i++)
	{
		printf("%3d", nums[i]);
	}
	printf("\n");
}

void printarray(Array * arr)
{
	for (uint i = 0; i < arr->size; i++)
	{
		printf("%3d", arr->array[i]);
	}
	printf("\n");
}

void swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
