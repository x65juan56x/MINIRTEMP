/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 21:51:30 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/14 14:41:38 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wrdctr(char const *s, char c)
{
	size_t	i;
	size_t	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			w++;
			while (s[i] != c && s[i])
				i++;
			if (!s[i])
				return (w);
		}
		else
			i++;
	}
	return (w);
}

static void	*ft_freearr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**arr;

	arr = (char **)malloc((ft_wrdctr(s, c) + 1) * sizeof(char *));
	if (!arr || !s)
		return (NULL);
	i = -1;
	k = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			j = i;
			while (s[i] != c && s[i])
				i++;
			arr[k] = ft_substr(s, j, (i - j));
			if (!arr[k++])
				return (ft_freearr(arr));
			i--;
		}
	}
	arr[k] = 0;
	return (arr);
}
/*
i; = Index to iterate through the string
j; = Index to mark the start of a word
k; = Index to count words and fill the string array
**arr; // Resulting array of strings
Line 59: Allocates memory for the string array, with an extra for the final NULL.
Line 62: Initializes i to -1 to compensate for the ++i at the start of the while.
Line 63: Initializes the word counter.
Line 64: Iterates over each character of the string.
Line 66: Finds the start of a word (not a separator).
Line 68: Marks the start of the word.
Line 69: Finds the end of the word.
Line 71: Creates a substring from j to i and assigns it to the array "arr".
Line 74: Decrements i to avoid skipping characters.
*/

// #include <stdio.h>

// int main() {
// 	const char *s = "Hello world this is a test";
// 	char c = ' ';
// 	char **result;
// 	int i = 0;

// 	printf("ft_split\n");
// 	printf("Original string: '%s'\n", s);
// 	printf("Delimiter: '%c'\n", c);
// 	result = ft_split(s, c);
// 	if (result != NULL)
// 	{
// 		while (result[i] != NULL)
// 		{
// 			printf("Result[%d]: '%s'\n", i, result[i]);
// 			free(result[i]);
// 			i++;
// 		}
// 		free(result);
// 	}
// 	else
// 		printf("ft_split returned NULL\n");
// 	return (0);
// }
