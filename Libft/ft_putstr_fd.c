/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:45:32 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/05 12:45:36 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != 0)
	{
		write(fd, s, 1);
		s++;
	}
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
// 	printf("ft_putstr_fd\n");
// 	printf("String to write: '%s'\n", str);
// 	ft_putstr_fd(str, fd);
// 	close(fd);
// 	printf("String written to 'output.txt'\n");
// 	return (0);
// }
