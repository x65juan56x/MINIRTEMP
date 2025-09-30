/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:37:29 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/04 22:37:36 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}
// #include <stdio.h>

// int main()
// {
// 	const char *s1 = "Hello, ";
// 	const char *s2 = "world!";
// 	char *joined_str;

// 	printf("ft_strjoin\n");
// 	printf("String 1: '%s'\n", s1);
// 	printf("String 2: '%s'\n", s2);
// 	joined_str = ft_strjoin(s1, s2);
// 	if (joined_str != NULL)
// 	{
// 		printf("Resulting joined string: '%s'\n", joined_str);
// 		free(joined_str);
// 	}
// 	else
// 		printf("ft_strjoin returned NULL\n");
// 	return (0);
// }
