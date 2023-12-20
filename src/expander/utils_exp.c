/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:15:24 by ojimenez          #+#    #+#             */
/*   Updated: 2023/12/20 14:25:50 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//si no va hacer con strncmp
int	count_pipes(t_tokens *tokens)
{
	int		count;
	size_t	i;

	count = 0;
	i = 0;
	while (i < tokens->size)
	{
		if (tokens->words[i].word && tokens->words[i].word[0] == '|')
			count++;
		i++;
	}
	return (count);
}

//nos dice cuantas palabras van a ir en cada matriz
int	len_to_expand(t_tokens *t, int *flag)
{
	char	*s;
	int		cont;
	int		i_aux;

	cont = 0;
	i_aux = t->i_exp;
	while (t->i_exp < (int)t->size)
	{
		s = t->words[t->i_exp].word;
		if (s[0] && s[0] != '<' && s[0] != '>' && s[0] != '|')
		{
			if (s[0] != ' ')
				cont++;
			(t->i_exp)++;
		}
		else
		{
			if (s[0])
				*flag = 1;
			break ;
		}
	}
	t->i_exp = i_aux;
	return (cont);
}

void	create_node(t_expander **nodo)
{
	(*nodo)->next = malloc(sizeof(t_expander));
	if (!(*nodo)->next)
	{
		perror("Error al asignar memoria para un nodo");
		exit(EXIT_FAILURE);
	}
	(*nodo)->next->next = NULL;
	(*nodo)->next->prev = *nodo;
}

//caldra lliberar
void	malloc_error(void)
{
	perror("Error al asignar memoria en un malloc");
	exit(EXIT_FAILURE);
}
