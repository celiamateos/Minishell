/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:57:40 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/20 16:44:58 by daviles-         ###   ########.fr       */
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
			if ((*tree)->right == NULL)
				(*tree)->right = new_leaf(token);
			else
			{
				printf("Token CMD, tree->right not empty\n");
				aux_leaf = *tree;
			while (aux_leaf->right)
				aux_leaf = aux_leaf->right;
			aux_leaf->right = new_leaf(token);
			//insert_leaf(&(*tree)->right, token_list);
			}
		}
		else if (token->type == PIPE)
		{
			if ((*tree)->content->type == PIPE)
			{
				aux_leaf = *tree;
				while ((aux_leaf->right)->content->type == PIPE)
					aux_leaf = aux_leaf->right;
				leaf = new_leaf(token);
				leaf->left = aux_leaf->right;
				aux_leaf->right = leaf;
//				insert_leaf(&(*tree)->right, token_list);
			}
			else
			{
				
				leaf = new_leaf(token);
				aux_leaf = *tree;
				leaf->left = aux_leaf;
				*tree = leaf;
			}	
		}
		else if (token->type == REDIR)
		{
			if ((*tree)->right == NULL)
				(*tree)->right = new_leaf(token);
			else
				insert_leaf(&(*tree)->right, token_list);
	
		}
		token_list = token_list->next;
	}
}

void	init_tree(t_shell_sack **sack)
{
	t_tree	*tree;
	t_tree	**root;
	t_token	*token;
	t_dlist	*token_list;
	t_tree	*leaf;
	t_tree	*aux_leaf;

	token_list = (*sack)->token_list;
	tree = new_leaf(token_list->content);
	token_list = token_list->next;
	//*root = tree; // guardar en sack
	insert_leaf(&tree, token_list);
	print_preorder(tree);
/*	while (tree)
	{
		token = tree->content;
       		printf("%s\n", token->value);
		tree = tree->right;
	}
*/
}
