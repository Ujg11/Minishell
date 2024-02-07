/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:39:58 by ojimenez          #+#    #+#             */
/*   Updated: 2024/02/07 15:14:01 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	destroy_exp_matrix(t_expander *exp)
{
	int	i;

	i = 0;
	if (!exp->exp_matr)
		return ;
	if (exp->exp_matr)
	{
		while (exp->exp_matr[i])
		{
			free(exp->exp_matr[i]);
			i++;
		}
	}
	free(exp->exp_matr);
}

void	destroy_expander(t_expander **exp)
{
	t_expander	*tmp;
	int			i;

	i = 0;
	if (!exp || !(*exp))
		return ;
	while (*exp)
	{
		tmp = (*exp)->next;
		destroy_exp_matrix(*exp);
		if ((*exp)->token)
			free((*exp)->token);
		free(*exp);
		*exp = tmp;
	}
	*exp = NULL;
}

void	destroy_tokens(t_tokens **t)
{
	int	i;

	i = 0;
	if (!t || !*t)
		return ;
	if ((*t)->words)
	{
		while (i < (int)(*t)->size)
		{
			free((*t)->words[i].word);
			i++;
		}
		free((*t)->words);
		(*t)->words = NULL;
	}
	free(*t);
	*t = NULL;
}

void	destroy_all(t_tokens **t, t_expander **exp, char *input)
{
	destroy_tokens(t);
	destroy_expander(exp);
	if (input)
		free(input);
}
