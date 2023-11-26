/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:12:30 by ojimenez          #+#    #+#             */
/*   Updated: 2023/11/26 17:41:02 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// INP, OUTP, PIPE
int	exp_type(t_tokens *tokens, int pos)
{
	int	type;

	type = -1;
	if (i >= 1)
	{
		if (tokens->words[ ]->word[0] == '<')
			type = INP;
		if (tokens->words[ ]->word[0] == '>')
			type = OUTP;
		if (tokens->words[ ]->word[0] == '|')
			type = PIPE;
		//faltaria mirar si 
	}
	return (type);
}

int	expander(t_tokens *tokens)
{
	t_expansor	*exp;
	int			i;

	exp->pipe_cont = count_pipes(tokens);
	i = 0;
	while (i < tokens->size)
	{
		
		exp->exp_type = 
		i++;
	}
}
