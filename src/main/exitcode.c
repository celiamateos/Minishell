/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:18:55 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:40:55 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

// @brief Wait for the PID received to end, and returns exitcode.
int	wait_exitcode(int last_pid)
{
	int	curr_pid;
	int	exit_code;
	int	status;

	exit_code = 0;
	curr_pid = 0;
	while (curr_pid != -1)
	{
		curr_pid = waitpid(-1, &status, 0);
		if (curr_pid == last_pid)
		{
			if (WIFEXITED(status))
			{
				exit_code = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				exit_code = WTERMSIG(status) + 128;
				if (exit_code == 130 || exit_code == 131)
					write(1, "\n", 1);
			}
		}
	}
	return (exit_code);
}

int	read_exit(char *line)
{
	if (!ft_strncmp(line, "exit", 5))
		return (1);
	else
		return (0);
}
