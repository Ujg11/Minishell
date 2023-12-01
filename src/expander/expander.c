/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:12:30 by ojimenez          #+#    #+#             */
/*   Updated: 2023/12/01 12:57:19 by ojimenez         ###   ########.fr       */
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
	num_pipes = count_pipes(tokens);//pasarlo como puntero hacia el main
	//Mentre que no arribem al final de la linea
	exp_split_to_expand(tokens, &exp);
	return (0);
}

//Faltara hacer las funciones de free de la lista y los tokens