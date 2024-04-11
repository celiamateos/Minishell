/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:57:40 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/20 16:44:58 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	leaf_isredirect_aux(t_tree **tree, t_dlist *token_list)
{
	t_token	*token;

	token = token_list->content;
	if (token->type >= 7 && (*tree)->right == NULL)
		(*tree)->right = new_leaf(token);
	else if (token->type >= 7 && (*tree)->right->content->type >= 7)
	{
		while ((*tree)->right)
			(*tree) = (*tree)->right;
		(*tree)->right = new_leaf(token);
	}
	else if (token->type >= 5 && (*tree)->left == NULL)
		(*tree)->left = new_leaf(token);
	else if (token->type >= 5 && (*tree)->left->content->type >= 5)
	{
		while ((*tree)->left)
			(*tree) = (*tree)->left;
		(*tree)->left = new_leaf(token);
	}
	else if (((*tree)->content->type >= 1 && (*tree)->content->type <= 4)
		&& (*tree)->right == NULL)
		(*tree)->right = new_leaf(token);
	else if ((*tree)->content->type >= 1 && (*tree)->content->type <= 4)
		return (0);
	return (1);
}
