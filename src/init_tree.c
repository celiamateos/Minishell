/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:57:40 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/10 19:57:43 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	
}

void	print_tree(void *content)
{
	t_token	token;

	token = content;
	printf("%s\n", token->value);
}

t_tree	new_leaf(t_token *token)
{
	t_tree	leaf;

	if (!token)
		return (NULL);
	leaf = malloc(sizeof(t_tree));
	leaf->content = token;
	leaf->left = NULL;
	leaf->right = NULL;
	return (leaf);
}

void	add_left_tree(t_tree *tree, t_tree *leaf)
{
	if (!leaf || !tree)
		return ;
	tree->left = leaf;
}

void	add_right_tree(t_tree *tree, t_tree *leaf)
{
	if (!leaf || !tree)
		return ;
	tree->right = leaf;
}

void	init_tree(t_dlist *tokens)
{
	t_tree	*tree_node;
	t_tree	*root;
	t_token	token;

//	tree = NULL;
	tree_node = new_leaf(tokens->content);
	tokens = tokens->next;
	root = tree_node;
	while (tokens)
	{
		token = tokens->content;
		if (token->type == PIPE)
		{
			root = new_leaf(tokens->content);
			add_left_tree(root, tree_node);
		}
		else if (token->type == CMD)
		{
			//go next token and check if is operator
			tree_node = new_leaf(tokens->content);
		}
		tokens = tokens->next;
	}
}
