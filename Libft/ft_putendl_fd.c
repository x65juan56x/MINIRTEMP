/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:52:41 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/05 12:52:50 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
// #include <fcntl.h>
// #include <unistd.h>

// int main()
// {
// 	char *str = "Hello, world!";
// 	int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	printf("ft_putendl_fd\n");
// 	printf("String to write: '%s'\n", str);
// 	ft_putendl_fd(str, fd);
// 	close(fd);
// 	printf("String with newline written to 'output.txt'\n");
// 	return (0);
// }
