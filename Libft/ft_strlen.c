/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:30:44 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/02 15:31:04 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	n;

	n = 0;
	while (*str != 0)
	{
		n++;
		str++;
	}
	return (n);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char *str = "Hello, world!";
// 	printf("ft_strlen vs. strlen\n");
// 	printf("Original strlen: %zu\n", strlen(str));
// 	printf("libft ft_strlen: %zu\n", ft_strlen(str));
// 	return (0);
// }
