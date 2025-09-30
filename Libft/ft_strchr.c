/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:54:09 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/14 15:08:34 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	chr;
	char	*str;

	chr = (unsigned char)c;
	str = (char *)s;
	i = 0;
	while (s[i])
	{
		if (s[i] == chr)
			return (str + i);
		i++;
	}
	if (chr == s[i])
		return (str + i);
	return (NULL);
}
/*
Line 21:
    Assign "chr" the value of "c" cast as (unsigned char) to avoid issues
    when "c" has values outside the ASCII character range (256 < c < 0).
Line 22:
    I could avoid using the "str" variable by directly returning
    ((char *)s + i); on line 27, but casting in each loop iteration is
	inefficient.
*/

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	const char *str = "Hello, world!";
// 	int c = 'o';

// 	printf("ft_strchr vs. strchr\n");
// 	printf("String: %s\n", str);
// 	printf("Character: %c\n", c);
// 	printf("Original strchr: %s\n", strchr(str, c));
// 	printf("libft ft_strchr: %s\n", ft_strchr(str, c));
// 	return (0);
// }
