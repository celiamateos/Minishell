/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 01:21:01 by daviles-          #+#    #+#             */
/*   Updated: 2023/11/19 19:22:15 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
#include "automata.h"

void	automata_init(t_automata *a, void *data, t_dlist **token_list)
{
	alphabet_init(a);
	errors_init(a);
	sactions_init(a);
	tactions_init(a);
	a->data = data;
	a->token_list = token_list;
	a->get_state = get_state;
}

// @brief This function validates the syntax of cmds, opers and redirs
int    validate_tokens(t_dlist *token_list)
{
	t_automata	a;
	t_token		info;
	int			finalstate;

	ft_bzero(&a, sizeof(t_automata));
	ft_bzero(&info, sizeof(t_token));
	automata_init(&a, &info, &token_list);
	if (token_list == NULL)
		return (1);
	finalstate = evaluate(&a);
	printf("FINAL %d ErrorLEN %d\n",finalstate, a.errorlen);
	if (finalstate >= a.errorlen)
	{
		return (0);
	}
	
	return (finalstate);
}
