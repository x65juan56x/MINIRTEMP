/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:24:56 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/12 12:24:58 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*aux;

	if (!lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = aux;
	}
	*lst = 0;
}
// #include <stdio.h>
// #include <stdlib.h>

// Función de ejemplo para eliminar contenido
// void del(void *content) 
// {
// 	free(content);
// }

// int main() 
// {
// 	int *value1 = malloc(sizeof(int));
// 	int *value2 = malloc(sizeof(int));
// 	int *value3 = malloc(sizeof(int));
// 	if (value1 == NULL || value2 == NULL || value3 == NULL)
// 	{
// 		perror("Error allocating memory");
// 		return (1);
// 	}
// 	*value1 = 42;
// 	*value2 = 21;
// 	*value3 = 84;

// 	t_list *head;
// 	t_list *second;
// 	t_list *third;
// 	printf("ft_lstclear\n");
// 	head = ft_lstnew(value1);
// 	second = ft_lstnew(value2);
// 	third = ft_lstnew(value3);
// 	head->next = second;
// 	second->next = third;
// 	ft_lstclear(&head, del);
// 	if (head == NULL) 
// 		printf("List cleared successfully\n");
// 	else
// 		printf("ft_lstclear failed\n");
// 	return (0);
// }
