/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:53:46 by daviles-          #+#    #+#             */
/*   Updated: 2023/10/31 05:12:24 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../include/minishell.h"

int	check_argerror(int ac, char **av, char *line)
{
	int	i;
	
	(void)ac;
	i = 0;
	while(av[i])
	{
		printf("Line: %s\n", line);
	}
	return (1);
}

t_token	*init_tokens(void)
{
	t_token	*tokens;
	t_token	*token;
	char	*av;
	char	**avs;
	int	i = 0;
	
	av = "file cat wc out";
	avs = ft_split(av, ' ');
	token = NULL;
	tokens = NULL;
	while (avs[i])
	{
		token = ft_dlstnew(avs[i]);
		ft_dlstadd_back(&tokens, token);
		i++;
	}
	return (tokens);

}
