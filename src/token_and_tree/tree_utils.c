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

void	leaf_isoperpipe(t_tree ***root, t_dlist *token_list)
{
	t_tree	**tree;
	t_tree	*aux_leaf;
	t_tree	*leaf;
	t_token	*token;

	token = token_list->content;
	tree = *root;
	if ((*tree)->content->type >= PIPE && (*tree)->content->type <= PARENT_OP)
	{
		aux_leaf = *tree;
		while ((aux_leaf->right)->content->type >= PIPE
			&& (aux_leaf->right)->content->type <= PARENT_OP)
			aux_leaf = aux_leaf->right;
		leaf = new_leaf(token);
		leaf->left = aux_leaf->right;
		aux_leaf->right = leaf;
	}
	else
	{
		leaf = new_leaf(token);
		aux_leaf = *tree;
		leaf->left = aux_leaf;
		*tree = leaf;
	}
}

void	leaf_isparenthesis_cl(t_tree ***root, t_dlist *token_list)
{
	t_tree	**tree;
	t_tree	*aux_leaf;
	t_tree	*last_parent;
	t_token	*aux_token;
	char	*value;

	(void)token_list;
	tree = *root;
	aux_leaf = *tree;
	aux_token = aux_leaf->content;
	while (aux_leaf->right)
	{
		if (aux_token->type == PARENT_OP)
			last_parent = aux_leaf;
		aux_leaf = aux_leaf->right;
		aux_token = aux_leaf->content;
	}
	value = last_parent->content->value;
	last_parent->content->type = PARENT_CL;
	last_parent->content->value = ft_strdup("()");
	free(value);
}

void	leaf_isparenthesis_op(t_tree ***root, t_dlist *token_list)
{
	t_tree	**tree;
	t_tree	*aux_leaf;
	t_token	*token;

	token = token_list->content;
	tree = *root;
	if ((*tree)->right == NULL)
		(*tree)->right = new_leaf(token);
	else
	{
		aux_leaf = *tree;
		while (aux_leaf->right)
			aux_leaf = aux_leaf->right;
		aux_leaf->right = new_leaf(token);
	}
}

t_tree	*new_leaf(t_token *token)
{
	t_tree	*leaf;

	leaf = malloc(sizeof(t_tree));
	if (!leaf)
		return (NULL);
	leaf->content = token;
	leaf->left = NULL;
	leaf->right = NULL;
	return (leaf);
}
