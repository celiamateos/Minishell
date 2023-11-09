/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:07:18 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/08 22:30:54 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

t_token	*init_tokens(char *line)
{
	t_token	*tokens;
	t_token	*token;
//	char	*av;
	char	**avs;
	int	i = 0;

//	av = "file cat wc out";
	avs = ft_split(line, ' ');
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

