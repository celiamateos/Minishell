/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos <cmateos-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:22:11 by cmateos           #+#    #+#             */
/*   Updated: 2023/11/10 19:58:02 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

//Recibe el primer nodo de una lista y retorna el número 
//de nodos total de la lista.
int	ft_dlstsize(t_dlist *lst)
{
	int		i;
	t_dlist	*temp;

	temp = lst;
	i = 0;
	if (temp)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
			i++;
		}
		if (temp->next == NULL)
			i++;
	}
	return (i);
}

void	del_dlst(void *content)
{
	if (content)
		free (content);
}

void	ft_dlstdelone(t_dlist *lst, void (*del_dlst)(void *))
{
	if (!del_dlst)
		return ;
	if (lst)
	{
		del_dlst(lst->content);
		free(lst);
	}
}

void	ft_dlstclear(t_dlist **lst, void (*del_dlst)(void *))
{
	t_dlist	*temp;

	temp = *lst;
	while (*lst && lst)
	{
		temp = (*lst)->next;
		ft_dlstdelone(*lst, del_dlst);
		*lst = temp;
	}
}
