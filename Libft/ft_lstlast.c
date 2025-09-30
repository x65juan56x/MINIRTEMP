/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmondon <jmondon@student.42malaga.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:28:32 by jmondon           #+#    #+#             */
/*   Updated: 2024/12/12 12:28:36 by jmondon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
// #include <stdio.h>

// int main()
// {
// 	int value1 = 42;
// 	int value2 = 21;
// 	int value3 = 84;
// 	t_list *head;
// 	t_list *second;
// 	t_list *third;
// 	t_list *last;

// 	printf("ft_lstlast\n");
// 	head = ft_lstnew(&value1);
// 	second = ft_lstnew(&value2);
// 	third = ft_lstnew(&value3);
// 	head->next = second;
// 	second->next = third;
// 	last = ft_lstlast(head);
// 	if (last != NULL)
// 	{
// 		printf("Last node content: %d\n", *(int *)(last->content));
// 	}
// 	else
// 		printf("ft_lstlast returned NULL\n");
// 	free(third);
// 	free(second);
// 	free(head);
// 	return (0);
// }
