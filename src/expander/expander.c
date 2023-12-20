/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:12:30 by ojimenez          #+#    #+#             */
/*   Updated: 2023/12/20 14:24:50 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expander	*expander(t_tokens *tokens)
{
	t_expander	*exp;

	exp = malloc(sizeof(t_expander));
	if (!exp)
	{
		perror("Error al asignar memoria para un nodo");
		exit(EXIT_FAILURE);
	}
	exp->prev = NULL;
	exp->next = NULL;
	exp_expand_var(tokens);
	exp->num_pipes = count_pipes(tokens);
	exp_split_to_expand(tokens, &exp);
	return (exp);
}

//Faltara hacer las funciones de free de la lista y los tokens
/*
int	main(void)
{
	t_expander	*exp;
	t_tokens	*tokens;
	int			i;
	int			j;

	tokens = malloc(sizeof(t_tokens));
	tokens->words = malloc(9 * sizeof(t_word));

	tokens->words[0].word = ft_strdup("cd");
	tokens->words[0].len = ft_strlen("cd");

	tokens->words[1].word = ft_strdup(" ");
	tokens->words[1].len = ft_strlen(" ");

	tokens->words[2].word = ft_strdup("$LOGNAME");
	tokens->words[2].len = ft_strlen("$LOGNAME");

	tokens->words[3].word = ft_strdup("'$PATH'");
	tokens->words[3].len = ft_strlen("'$PATH'");

	tokens->words[4].word = ft_strdup("|");
	tokens->words[4].len = ft_strlen("|");

	tokens->words[5].word = ft_strdup("ls");
	tokens->words[5].len = ft_strlen("ls");

	tokens->words[6].word = ft_strdup("-l");
	tokens->words[6].len = ft_strlen("-l");

	tokens->words[7].word = ft_strdup(">");
	tokens->words[7].len = ft_strlen(">");

	tokens->words[8].word = ft_strdup("archivo");
	tokens->words[8].len = ft_strlen("archivo");

	tokens->size = 9;

	exp = expander(tokens);
	i = 1;
	j = 0;
	while (exp)
	{
		printf("Nodo %d:\nTipo:%d\nLen = %d\n", i, exp->exp_type, exp->len);
		while (j < exp->len + 1)
		{
			printf("%s\n", exp->exp_matr[j]);
			j++;
		}
		j = 0;
		i++;
		exp = exp->next;
	}
	return (0);
}*/
