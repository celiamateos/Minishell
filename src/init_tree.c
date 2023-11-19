/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:57:40 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 18:32:05 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void print_preorder(t_tree *node) 
{
	t_token	*token;

	if (node != NULL) 
	{
		token = node->content;
       		printf("%s\n", token->value);
	        print_preorder(node->left);
	        print_preorder(node->right);
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

void	insert_leaf(t_tree **tree, t_dlist *token_list)
{
	t_token	*token;
	t_tree	*leaf;
	t_tree	*aux_leaf;

	if (token_list == NULL || !*tree || !tree)
		return ;
	while (token_list)
	{
		token = token_list->content;
		if (token->type == CMD)
		{
			if ((*tree)->left == NULL)
				(*tree)->left = new_leaf(token);
	//		else
	//			insert_leaf(&(*tree)->left, token_list);
	
		}
		else if (token->type == PIPE)
		{
			leaf = new_leaf(token);
	/*		if ((*tree)->left == NULL)
				insert_leaf(&(*tree)->right, token_list);
			else
				leaf->left = (*tree)->left;
			*tree = leaf;
	*/
			aux_leaf = *tree;
	//		while (aux_leaf->left)
	//			aux_leaf = aux_leaf->left;
			leaf->left = aux_leaf;
			insert_leaf(&(*tree)->right, token_list->next);
	//		aux_leaf = leaf;
	
		}
		else if (token->type == REDIR)
		{
	
		}
	}
}

void	init_tree(t_dlist *tokens)
{
	t_tree	*tree;
	t_tree	*root;
	t_token	*token;

	//tree = new_leaf("Root");
	tree = new_leaf(tokens->content);
	tokens = tokens->next;
	root = tree;
/*	while (tokens)
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
*/	while (tokens)
	{
		insert_leaf(&tree, tokens);
		tokens = tokens->next;
	}
	print_preorder(root);
}
