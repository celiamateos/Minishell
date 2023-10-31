/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:53:46 by daviles-          #+#    #+#             */
/*   Updated: 2023/10/31 02:30:53 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../../include/minishell.h"

int	check_argerror(int ac, char **av, char *line)
{
	int	i;

	i = 0;
	while(av[i])
	{
		printf("Line: %s\n", line);
	}
	return (1);
}

t_list	init_tokens(void)
{
	t_list	**tokens;
	t_list	*token;
	char	*av;
	char	**avs;
	int	i = 1;
	
	av = "file cat cat wc out";
	avs = ft_split(av, " ");
	token = ft_lst
	while (avs[i])
	{
		
	}

}
