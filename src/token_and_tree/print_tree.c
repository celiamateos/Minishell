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

// Function to print binary tree in 2D
// It does reverse inorder traversal
void	print2d_util(t_tree *root, int space)
{
	t_token	*token;
	int		i;

	if (root == NULL)
		return ;
	space += COUNT;
	print2d_util(root->right, space);
	ft_printf("\n");
	i = COUNT;
	while (i < space)
	{
		ft_printf(" ");
		i++;
	}
	token = root->content;
	printf("%s\n", token->value);
	print2d_util(root->left, space);
}

// Wrapper over print2d_util()
void	print2d(t_tree *root)
{
	print2d_util(root, 0);
}

void	print_preorder(t_tree *node)
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
