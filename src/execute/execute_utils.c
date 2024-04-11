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
#include "../../include/minishell.h"

/* @brief to take off lines on run_node. Check conditions of execution 
of operators. */
// @return 1 if it can be executed
int	check_opercondition(t_shell_sack ***sack, t_tree **node)
{
	if ((*node)->content->oper != 0)
		(**sack)->oper_state = (*node)->content->oper;
	if ((**sack)->oper_state == AND && (**sack)->last_exit == 0)
		return (1);
	else if ((**sack)->oper_state == OR && (**sack)->last_exit != 0)
		return (1);
	else if ((**sack)->oper_state == 0)
		return (1);
	else
		return (0);
}

/* @brief Find in tree the next cmd token or parenthesis. Used to add
 operator flag, that in execution it will execute or not depends on exitcode*/
t_tree	*findnext_cmdleaf(t_tree **node)
{
	t_token	*token;

	token = (*node)->content;
	if (token->type != CMD || token->type != PARENT_CL)
	{
		if ((*node)->left != NULL)
			if (((*node)->left)->content->type == CMD
				|| ((*node)->left)->content->type == PARENT_CL)
				return ((*node)->left);
		if ((*node)->right != NULL)
			if (((*node)->right)->content->type == CMD
				|| ((*node)->right)->content->type == PARENT_CL)
				return ((*node)->right);
	}
	return ((*node));
}

/*@brief create heredoc file and fill with stdin input. Close before reopen
to assign fd.*/
void	ft_heredoc(t_shell_sack *****sack_orig, char *eof)
{
	char			*line;
	int				fd_in;
	t_shell_sack	**sack;

	sack = ***sack_orig;
	fd_in = (*sack)->old_pipes[0];
	while (1)
	{
		ft_putstr_fd("\033[0;36mheredoc >\033[0m", 1);
		line = get_next_line(0);
		if (line == 0)
		{
			ft_putstr_fd("\nbash: warning: here-document delimited by \
			end-of-file (wanted eof)\n", 2);
			break ;
		}
		if (!ft_strncmp(line, eof, ft_strlen(eof))
			&& (1 + ft_strlen(eof)) == ft_strlen(line))
			break ;
		write(fd_in, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd_in);
}

/* @brief assign fd and open attreibutes deppends on redirection */
int	open_redirect(t_shell_sack ****sack_orig, t_tree *node)
{
	t_token			*token;
	t_shell_sack	**sack;

	token = node->content;
	sack = **sack_orig;
	if (token->type == HEREDOC)
	{
		(*sack)->old_pipes[0] = open(".heredoc",
				O_RDWR | O_CREAT | O_TRUNC, 0666);
		ft_heredoc(&sack_orig, token->value);
		(*sack)->old_pipes[0] = open(".heredoc", O_RDONLY, 0666);
		(*sack)->heredoc = 1;
	}
	else if (token->type == REDIR_IN)
		(*sack)->old_pipes[0] = open(token->value, O_RDONLY);
	else if (token->type == REDIR_OUT)
		(*sack)->new_pipes[1] = open(token->value,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (token->type == APPEND_OUT)
		(*sack)->new_pipes[1] = open(token->value,
				O_RDWR | O_CREAT | O_APPEND, 0666);
	if ((*sack)->old_pipes[0] == -1 || (*sack)->new_pipes[1] == -1)
		return (1);
	else
		return (0);
}

/* @brief check if cmd has redirection, and if it has, calls open_redirect 
to assign fds*/
int	check_redirect(t_shell_sack ***sack_orig, t_tree *node)
{
	int		i;
	t_tree	*aux_node;
	t_tree	*aux_node2;

	i = 0;
	aux_node = node;
	aux_node2 = node;
	if (aux_node != NULL)
	{
		if (aux_node->left && aux_node->left->content->type >= HEREDOC)
		{
			while (aux_node->left != NULL)
				aux_node = (aux_node)->left;
			i = open_redirect(&sack_orig, aux_node);
		}
		if (aux_node2->right && aux_node2->right->content->type >= HEREDOC)
		{
			while (aux_node2->right != NULL)
				aux_node2 = (aux_node2)->right;
			i = open_redirect(&sack_orig, aux_node2);
		}
	}
	return (i);
}
