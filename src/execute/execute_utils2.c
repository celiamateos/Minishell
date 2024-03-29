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

void	getcmd_redirect(t_shell_sack ***sack_orig, t_tree *node)
{
	t_shell_sack	**sack;

	sack = *sack_orig;
	if (check_redirect(&sack, node))
	{
		(*sack)->last_exit = 1;
		perror_free_exit("Open error", &sack);
	}
	if ((*sack)->old_pipes[0] != 0 && check_isbuiltin(node))
		if (dup2 ((*sack)->old_pipes[0], STDIN_FILENO) == -1)
			perror_free_exit("Dup2 error IN", &sack);
	if ((*sack)->new_pipes[1] != 1)
		if (dup2 ((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
			perror_free_exit("Dup2 error OUT", &sack);
	ft_close((*sack)->new_pipes[0], (*sack)->new_pipes[1]);
	ft_close((*sack)->old_pipes[0], (*sack)->old_pipes[1]);
}

/* @brief When an operator is found on tree node, find next nearest command or
parenthesis at his right. Then change the value of the paremeter token->oper 
to respective operator.
@parameters This function receive the sack and current tree node. */
void	run_oper(t_shell_sack ***sack_orig, t_tree *node)
{
	t_token	*token;
	t_tree	*aux_node;

	(void)sack_orig;
	token = (node)->content;
	aux_node = findnext_cmdleaf(&node->right);
	if (aux_node != NULL)
	{
		if (!ft_strncmp(token->value, "||", 3))
			aux_node->content->oper = OR;
		else if (!ft_strncmp(token->value, "&&", 3))
			aux_node->content->oper = AND;
	}
}

/*@brief Creates new pipes and backup the old ones. 
Protect to not allow pipe in last node to not change std.
	(DAVID -I have tocheck thath)*/
void	run_pipe(t_shell_sack ***sack_orig, t_tree *node)
{
	t_shell_sack	**sack;
	t_tree			*aux_node;

	aux_node = findnext_cmdleaf(&node->left);
	if (aux_node != NULL )
	{
		if (aux_node->content->oper != 0)
		{
			if ((**sack_orig)->old_pipes[0] != 0)
			{
				ft_close((**sack_orig)->old_pipes[0],
					(**sack_orig)->old_pipes[1]);
				(**sack_orig)->old_pipes[0] = 0;
				if (dup2 (0, STDIN_FILENO) == -1)
					perror_free_exit("Dup2 error IN", &*sack_orig);
			}
		}
	}
	sack = *sack_orig;
	(*sack)->old_pipes[0] = (*sack)->new_pipes[0];
	(*sack)->old_pipes[1] = (*sack)->new_pipes[1];
	if (pipe((*sack)->new_pipes) == -1)
		perror_free_exit("Pipe error", sack_orig);
}

void	ft_cpypipes(int *old_pipe, int *new_pipe)
{
	old_pipe[0] = new_pipe[0];
	old_pipe[1] = new_pipe[1];
}

/* @brief Close fds sended as parameters. Has protection to not close STDs*/
void	ft_close(int fd1, int fd2)
{
	if (fd1 > 2)
		close(fd1);
	if (fd2 > 2)
		close(fd2);
}
