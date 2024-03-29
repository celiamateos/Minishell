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

void	free_automata(t_automata *a)
{
	ft_freematrix(&a->alphabet);
	ft_freematrix(&a->errors);
}

void	automata_init(t_automata *a, t_dlist **token_list)
{
	alphabet_init(a);
	errors_init(a);
	a->token_list = token_list;
	a->get_state = get_state;
}

// @brief This function validates the syntax of cmds, opers and redirs
// @return 0 if success, else code error. Check code on errors_init()
int	validate_tokens(t_dlist *token_list, t_shell_sack ***sack)
{
	t_automata	a;
	int			finalstate;

	ft_bzero(&a, sizeof(t_automata));
	automata_init(&a, &token_list);
	if (token_list == NULL)
		return (1);
	finalstate = evaluate(&a);
	if (finalstate >= a.errorlen)
		return (free_automata(&a), 0);
	(**sack)->last_exit = 2;
	ft_putstr_fd(a.errors[finalstate], 2);
	ft_putstr_fd("\n", 2);
	return (free_automata(&a), finalstate);
}
