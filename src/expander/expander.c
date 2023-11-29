/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:12:30 by ojimenez          #+#    #+#             */
/*   Updated: 2023/11/29 18:47:25 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expander(t_tokens *tokens)
{
	t_expander	*exp;
	int			i;
	int			num_pipes;

	exp = malloc(sizeof(t_expander));
	if (!exp)
	{
		perror("Error al asignar memoria para un nodo");
		exit(EXIT_FAILURE);
	}
	exp->prev = NULL;
	exp_expand_var(tokens);
	num_pipes = count_pipes(tokens);
	//Mentre que no arribem al final de la linea
	exp_split_to_expand(tokens, exp);
}
