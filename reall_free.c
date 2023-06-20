
#include <stddef.h>
#include "shell.h"
#include <stdlib.h>

/**
 * __realloc - Reallocates a memory block using malloc and free.
 * @ptr: Pointer to the previously allocated memory block.
 * @size: The new size for the memory block.
 *
 * Return: Pointer to the reallocated memory block, or NULL on failure.
 */
void *__realloc(void *ptr, size_t size)
{
	void *new_ptr;
	size_t i;

	if (size == 0)
	{
		free(ptr);
		return NULL;
	}

	if (ptr == NULL)
		return malloc(size);

	new_ptr = malloc(size);
	if (new_ptr != NULL)
	{
		char *char_ptr = new_ptr;
		char *old_ptr = ptr;

		for (i = 0; i < size; i++)
			char_ptr[i] = old_ptr[i];

		free(ptr);
	}

	return new_ptr;
}


