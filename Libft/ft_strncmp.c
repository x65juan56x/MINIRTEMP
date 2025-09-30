/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:10:20 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/12 21:56:13 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	const char *s1 = "Hello, world!";
// 	const char *s2 = "Hello, everyone!";
// 	size_t n = 5;

// 	printf("ft_strncmp vs. strncmp\n");
// 	printf("Strings: '%s' and '%s'\n", s1, s2);
// 	printf("Length to compare: %zu\n", n);
// 	printf("Original strncmp: %d\n", strncmp(s1, s2, n));
// 	printf("libft ft_strncmp: %d\n", ft_strncmp(s1, s2, n));
// 	return (0);
// }
