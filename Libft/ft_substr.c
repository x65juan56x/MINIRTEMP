/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:33:37 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/14 14:24:46 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (start >= ft_strlen(s))
	{
		str = ft_calloc(1, sizeof(char));
		if (!str)
			return (NULL);
		return (str);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	str = (char *)ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (NULL);
	i = start;
	while (s[i] && ((i - start) < len))
	{
		str[i - start] = s[i];
		i++;
	}
	return (str);
}
/*
Lines 20 to 26:
    Ensure that if the start of the copy is set to a position beyond the
    length of the string, it returns a pointer to an empty string (calloc
    takes care of allocating and ensuring it is empty).
Lines 27 and 28:
    If the length from the start of the copy to the end of the original
    string is less than the length to be copied, reassign this length to
    avoid unnecessary memory allocation.
Using calloc for memory allocation means I don't have to worry about
adding the NULL character at the end of the string.
*/

// #include <stdio.h>

// int main()
// {
// 	const char *s = "Hello, world!";
// 	unsigned int start = 7;
// 	size_t len = 5;
// 	char *substr;

// 	printf("ft_substr\n");
// 	printf("Original string: '%s'\n", s);
// 	printf("Start position: %u\n", start);
// 	printf("Length: %zu\n", len);
// 	substr = ft_substr(s, start, len);
// 	if (substr != NULL)
// 	{
// 		printf("Resulting substring: '%s'\n", substr);
// 		free(substr);
// 	}
// 	else
// 		printf("ft_substr returned NULL\n");
// 	return (0);
// }
