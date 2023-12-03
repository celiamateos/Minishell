/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:18:55 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:40:55 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../include/minishell.h"

void    open_redirect(t_shell_sack **sack, t_tree *node)
{
    t_token *token;

    token = node->content;
    if (token->type >= HEREDOC)
        (*sack)->old_pipes[0] = open("tmp/.heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
    else if (token->type >= REDIR_IN)
        (*sack)->old_pipes[0] = open(token->value, O_RDONLY);
    else if (token->type >= REDIR_OUT)
        (*sack)->new_pipes[1] = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    else if (token->type >= APPEND_OUT)
        (*sack)->new_pipes[1] = open(token->value, O_RDWR | O_CREAT | O_APPEND, 0666);
    if ((*sack)->new_pipes[0] == -1 || (*sack)->new_pipes[1] == -1)
        ft_perror_exit("Open error");
}

void    check_redirect(t_shell_sack **sack, t_tree *node)
{
    t_token *token;

    token = node->content;
    if (node->left && token->type >= HEREDOC)
        open_redirect(sack, node->left);
    if (node->right && token->type >= HEREDOC)
        open_redirect(sack, node->right);   
}

void	ft_close(int fd1, int fd2)
{
    if (fd1)
	    close(fd1);
	if (fd2)
        close(fd2);
}