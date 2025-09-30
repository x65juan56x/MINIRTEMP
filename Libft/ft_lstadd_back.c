/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:24:02 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/12 12:24:06 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}
// #include <stdio.h>

// int main()
// {
// 	int value1 = 42;
// 	int value2 = 21;
// 	int value3 = 84;
// 	t_list *head;
// 	t_list *second;
// 	t_list *new_node;

// 	printf("ft_lstadd_back\n");
// 	head = ft_lstnew(&value1);
// 	second = ft_lstnew(&value2);
// 	head->next = second;
// 	new_node = ft_lstnew(&value3);
// 	ft_lstadd_back(&head, new_node);
// 	t_list *current = head;
// 	while (current != NULL)
// 	{
// 		printf("Node content: %d\n", *(int *)(current->content));
// 		current = current->next;
// 	}
// 	free(new_node);
// 	free(second);
// 	free(head);

// 	return (0);
// }
