/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:02:47 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/03 21:02:50 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	i;

	d = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (d == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	const char *str = "Hello, world!";
// 	char *dup1;
// 	char *dup2;

// 	printf("ft_strdup vs. strdup\n");
// 	printf("Source string: '%s'\n", str);
// 	dup1 = strdup(str);
// 	dup2 = ft_strdup(str);
// 	printf("Original strdup: %s\n", dup1);
// 	printf("libft ft_strdup: %s\n", dup2);
// 	free(dup1);
// 	free(dup2);
// 	return (0);
// }
