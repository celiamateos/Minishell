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
 # include "../include/minishell.h"
 //Crea un nuevo nodo con content char *, void *next y void*prev.
/*@brief ALOCA MEMORIA*/
t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*node;

	node = (t_dlist *)malloc(sizeof (t_dlist));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
 //Añade un nodo al final de la lista
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = NULL;
	}
	else
	{
		temp = ft_dlstlast(*lst);
		temp->next = new;
		new->prev = temp;
	}
}

//Añade un nodo al principio de la lista
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	if (lst)
	{
		if (*lst)
		{
			new->next = *lst;
			(*lst)->prev = new;
		}
		*lst = new;
	}
}
 //Recibe un nodo y recorre la lista hacia alante, retorna el último nodo de la lista
t_dlist	*ft_dlstlast(t_dlist *lst)
{
	t_dlist	*lastnode;

	lastnode = lst;
	if (lastnode)
	{
		while (lastnode->next != NULL)
			lastnode = lastnode->next;
	}
	return (lastnode);
}
 //Recibe un nodo y recorre la lista hacia atras, retorna el primer nodo de la lista
t_dlist *ft_dlstfirst(t_dlist *lst)
{
	t_dlist *first_node;

	first_node = lst;
	if (first_node)
	{
		while (first_node->prev != NULL)
			first_node = first_node->prev;
	}
	return (first_node);
}
 //Recibe el primer nodo de una lista y retorna el número de nodos total de la lista.
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

