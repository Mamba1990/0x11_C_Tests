#include <stddef.h>
#include <stdlib.h>
#include "shell.h"
/*
 * str_dup - duplicates a string
 * @str: string input
 *
 * Return: pointer to the duplicated string
 */
char *str_dup(const char *string)
{
	int len;
	char *_r;

	if (string == NULL)
		return (NULL);
	for (len = 0; *string++; len++)
		len++;
	_r = malloc(sizeof(char) * (len + 1));
	if (!_r)
		return (NULL);
	for (len++; len--;)
		_r[len] = *--string;
	return (_r);
}

/**
 * str_len - returns the length of a string
 * @s: string
 * Return: length of a string
 */
int str_len(char *s)
{
	int length;

	for (length = 0; *s != '\0'; length++)
	{
		s++;
	}
	return (length);
}

/**
* str_cmp - compares two string
* @s1: input string 1
* @s2: input string 2
* Return: s1[i] - s2[i]
*/
int str_cmp(char *s1, char *s2)
{
	int i = 0;

	for ( ; (*(s1 + i) != '\0') && (*(s2 + i) != '\0'); i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}

	}
	return (0);
}
/**
* str_cpy - copies the string pointed to by src
* @dest: copy to
* @src: copy from
* Return: string
*/
char *str_cpy(char *dest, char *src)
{
	int l = 0;
	int i = 0;

	while (*(src + l) != '\0')
	{
		l++;
	}
	for ( ; i < l ; i++)
	{
		dest[i] = src[i];
	}
	dest[l] = '\0';
	return (dest);
}
/**
* str_cat - concatenates two strings
* @dest: input
* @src: input
*
* Return: pointer to the resulting string dest
*/
char *str_cat(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	while (*(dest + i) != '\0')
	{
		i++;
	}
	while (*(src + j) != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
