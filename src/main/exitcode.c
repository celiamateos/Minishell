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
# include "../../include/minishell.h"

/// ESTE ES EL DE MI PIPEX PERO SOLO VALE PA DOS JEJE
// static void	ft_wait_process(int pid1, int pid2)
// {
// 	int	status;

// 	waitpid(pid1, &status, 0);
// 	if (WIFEXITED(status))
// 	{
// 		status = WEXITSTATUS(status);
// 		if (status != EXIT_SUCCESS)
// 			ft_error(0, NULL);
// 	}
// 	waitpid(pid2, &status, 0);
// 	if (WIFEXITED(status))
// 	{
// 		status = WEXITSTATUS(status);
// 		if (status != EXIT_SUCCESS)
// 			ft_error(0, NULL);
// 	}
// 	return (status);
// }

// // ESTE ES DE LA CHATI Y YO PENSABA QUE FUNCIONABA
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/wait.h>
// #include <unistd.h>

// int	wait_exitcode(int pid)
// {
//     int status;
//     int exit_status = 0;

//     if (pid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } else if (pid == 0) {
//         // printf("Soy el proceso hijo\n");
//         exit(EXIT_FAILURE);
//     } else {
//         // Código del proceso padre
//         waitpid(pid, &status, 0);

//         if (WIFEXITED(status))
// 		{
// 			exit_status = WEXITSTATUS(status);
//             printf("El código de salida del hijo fue: %d\n", exit_status);
//         }
//     }
//     return (exit_status);
// }


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
				// printf("STATUS :%d Exit_code: %d\n",WIFEXITED(status), exit_code);
			}
			else if (WIFSIGNALED(status))
			{
				exit_code = WTERMSIG(status) + 128;
				// printf("STATUS :%d STATUS :%d Exit_codeSIG: \n",WIFEXITED(status), exit_code);
			}
		}
	}
	return (exit_code);	
}

//// COPIA DE SEGURIDAD DEL DE DAVID POR SI ME DA POR ROMPERLO JEJE
// int	wait_exitcode(int last_pid)
// {
// 	int	curr_pid;
// 	int	exit_code;
// 	int	status;

// 	exit_code = 0;
// 	curr_pid = 0;
// 	while (curr_pid != -1)
// 	{
// 		curr_pid = waitpid(-1, &status, 0);
// 		if (curr_pid == last_pid)
// 		{
// 			if (WIFEXITED(status))
// 			{
// 				exit_code = WEXITSTATUS(status);
// 				// printf("STATUS :%d Exit_code: %d\n",WIFEXITED(status), exit_code);
// 			}
// 			else if (WIFSIGNALED(status))
// 			{
// 				exit_code = WTERMSIG(status) + 128;
// 				// printf("STATUS :%d STATUS :%d Exit_codeSIG: \n",WIFEXITED(status), exit_code);
// 			}
// 		}
// 	}
// 	return (exit_code);	
// }

int	read_exit(char *line)
{
	if(!ft_strncmp(line, "exit", 5))
		return(1);
	else
		return (0);
}