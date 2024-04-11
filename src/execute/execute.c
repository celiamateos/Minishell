/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:18:55 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:40:55 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	run_cmd_util(t_shell_sack ***sack_orig, t_tree *node)
{
	t_token			*token;
	char			*cmd;
	t_shell_sack	**sack;

	sack = *sack_orig;
	token = node->content;
	getcmd_redirect(&sack, node);
	if (!check_isbuiltin(node))
	{
		execute_builtin(&sack, node);
		exit((*sack)->last_exit);
	}
	else
	{
		remove_quotes_arr_cmds(token, &(*sack));
		cmd = getcmd_withpath(token->cmds[0], (*sack)->env->env);
		if (cmd)
			execve(cmd, token->cmds, (*sack)->env->env);
		free_exit(token->cmds, sack_orig, COMANDNOTFOUND);
	}
}

void	run_cmd(t_shell_sack ***sack_orig, t_tree *node)
{
	t_shell_sack	**sack;

	sack = *sack_orig;
	(*sack)->last_exit = 0;
	(*sack)->last_pid = fork();
	if ((*sack)->last_pid < 0)
		perror_free_exit("Fork error", &sack);
	else if ((*sack)->last_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		run_cmd_util(&sack, node);
	}
	ft_close((*sack)->old_pipes[0], (*sack)->new_pipes[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_cpypipes((*sack)->old_pipes, (*sack)->new_pipes);
	(*sack)->new_pipes[1] = 1;
}

/* @brief Executes appropriate function depends on type of token on tree. */
void	run_node(t_shell_sack **sack, t_tree **node)
{
	if (((*node)->content)->type == PARENT_CL)
	{
		if (!check_opercondition(&sack, node))
		{
			free_tree(&(*node)->right);
			(*node)->right = NULL;
		}
	}
	else if (((*node)->content)->type == CMD)
	{
		if (check_opercondition(&sack, node))
			run_cmd(&sack, (*node));
	}
	else if (((*node)->content)->type == PIPE)
	{
		++(*sack)->pipe_wc;
		run_pipe(&sack, (*node));
	}
	else if (((*node)->content)->type == OPER)
	{
		(*sack)->last_exit = wait_exitcode((*sack)->last_pid);
		run_oper(&sack, (*node));
	}
}

/* @brief Runs executor trough tree. This is the most common way but 
there's others.*/
void	run_preorder(t_tree *node, t_shell_sack **sack)
{
	if (node != NULL)
	{
		if (check_builtinparent(node) && (*sack)->pipe_wc == 0)
		{
			if (check_redirect(&sack, node))
			{
				(*sack)->last_exit = 1;
				perror_free_exit("Open error", &sack);
			}
			if ((*sack)->old_pipes[0] != 0)
				if (dup2((*sack)->old_pipes[0], STDIN_FILENO) == -1)
					perror_free_exit("Dup2 error IN", &sack);
			if ((*sack)->new_pipes[1] != 1)
				if (dup2((*sack)->new_pipes[1], STDOUT_FILENO) == -1)
					perror_free_exit("Dup2 error OUT", &sack);
			ft_close((*sack)->new_pipes[0], (*sack)->new_pipes[1]);
			ft_close((*sack)->old_pipes[0], (*sack)->old_pipes[1]);
			if (check_opercondition(&sack, &node) || (*sack)->oper_state == 0)
				(*sack)->last_exit = execute_builtin(&sack, node);
		}
		else
			run_node(sack, &node);
		run_preorder(node->left, sack);
		run_preorder(node->right, sack);
	}
}

void	execute(t_shell_sack **sack)
{
	t_tree	*tree;

	tree = (*sack)->tree_list;
	run_preorder(tree, sack);
	(*sack)->oper_state = 0;
	unlink(".heredoc");
	(*sack)->last_exit = wait_exitcode((*sack)->last_pid);
	free_sack(&(*sack));
}
