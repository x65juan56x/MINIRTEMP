/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:22:30 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/02 16:22:33 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (!((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z'))))
		return (0);
	return (1);
}
// #include <stdio.h>
// #include <ctype.h>

// int main()
// {
// 	char c = 'C';

// 	printf("ft_isalpha vs. isalpha\n");
// 	printf("Character: %c\n", c);
// 	printf("Original isalpha: %d\n", isalpha(c));
// 	printf("libft ft_isalpha: %d\n", ft_isalpha(c));
// 	printf("\n");
// 	return (0);
// }
