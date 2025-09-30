/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:25:24 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/12 12:25:27 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}
// #include <stdio.h>

// // Función de ejemplo para eliminar contenido
// void del(void *content) {
//     free(content);
// }

// int main()
// {
// 	int *value = malloc(sizeof(int));

// 	if (value == NULL)
// 	{
// 		perror("Error allocating memory");
// 		return 1;
// 	}
// 	*value = 42;
// 	t_list *node;
// 	printf("ft_lstdelone\n");
// 	printf("Content to delete: %d\n", *value);
// 	node = ft_lstnew(value);
// 	if (node != NULL)
// 	{
// 		printf("Node created successfully\n");
// 		printf("Node content: %d\n", *(int *)(node->content));
// 		ft_lstdelone(node, del);
// 		printf("Node deleted successfully\n");
// 	}
// 	else
// 		printf("ft_lstnew returned NULL\n");
// 	return (0);
// }
