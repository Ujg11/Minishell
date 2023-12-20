/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:04:43 by ojimenez          #+#    #+#             */
/*   Updated: 2023/12/20 14:20:51 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Miramos que no haya << o >> ya que tenemos que ponerlo, sino solo el '\0'
void	fill_last(t_tokens *t, t_expander **exp, int *i, int k)
{
	int	len;

	len = (int)t->words[k].len;
	(*exp)->exp_matr[*i] = malloc((t->words[k].len + 1) * sizeof(char));
	if (!(*exp)->exp_matr[*i])
	{
		perror("Error al asignar memoria en un malloc");
		exit(EXIT_FAILURE);
	}
	(*exp)->exp_matr[*i][0] = t->words[k].word[0];
	if (len == 2 && (t->words[k].word[1] == '<' || t->words[k].word[1] == '>'))
	{
		(*exp)->exp_matr[*i][1] = t->words[k].word[1];
		(*exp)->exp_matr[*i][2] = '\0';
	}
	else
		(*exp)->exp_matr[*i][1] = '\0';
	(*i)++;
}

//Rellena la matriz con las palabras que tocan y el operador.
//Los espacios no se ponen
void	fill_matrix_to_spand(t_tokens *t, t_expander **exp, int len, int flag)
{
	int	cont;
	int	i;
	int	j;

	i = 0;
	cont = 0;
	while (cont < len - flag)
	{
		j = -1;
		if (t->words[t->i_exp].word[0] == ' ')
			t->i_exp++;
		(*exp)->exp_matr[i] = malloc((t->words[t->i_exp].len + 1) 
				* sizeof(char));
		if (!(*exp)->exp_matr[i])
			malloc_error();
		while (++j < (int)t->words[t->i_exp].len)
			(*exp)->exp_matr[i][j] = t->words[t->i_exp].word[j];
		(*exp)->exp_matr[i][j] = '\0';
		i++;
		t->i_exp++;
		cont++;
	}
	if (flag)
		fill_last(t, exp, &i, t->i_exp);
	(*exp)->exp_matr[i] = NULL;
}

int	more_types(t_expander **exp, int len_act)
{
	int	len_prev;
	int	len;
	int	type;

	len_prev = (*exp)->prev->len - 1;
	len = len_act;
	type = NONE;
	if ((*exp)->exp_matr[len][0] == '<'
			&& (*exp)->prev->exp_matr[len_prev][0] == '|')
		type = INPIPE;
	if ((*exp)->exp_matr[len][0] == '>'
			&& (*exp)->prev->exp_matr[len_prev][0] == '|')
		type = OUTPIPE;
	if ((*exp)->prev->exp_matr[len_prev][0] == '|'
			&& (*exp)->exp_matr[len][0] == '<'
			&& (*exp)->exp_matr[len][1] == '<')
		type = HEREDOC_PIPE;
	if ((*exp)->prev->exp_matr[len_prev][0] == '|'
			&& (*exp)->exp_matr[len][0] == '>'
			&& (*exp)->exp_matr[len][1] == '>')
		type = APPEND_PIPE;
	return (type);
}

//Escogemos el tipo de expansor de nuestra matriz
int	exp_type_to_expand(t_expander **exp)
{
	int	type;
	int	len;

	type = NONE;
	len = (*exp)->len - 1;
	if ((*exp)->exp_matr[len][0] == '<' && (*exp)->exp_matr[len][1] == '\0')
		type = INP;
	if ((*exp)->exp_matr[len][0] == '>' && (*exp)->exp_matr[len][1] == '\0')
		type = OUTP;
	if ((*exp)->exp_matr[len][0] == '|')
		type = PIPE;
	if ((*exp)->exp_matr[len][0] == '<' && (*exp)->exp_matr[len][1] == '<')
		type = HEREDOC;
	if ((*exp)->exp_matr[len][0] == '>' && (*exp)->exp_matr[len][1] == '>')
		type = APPEND;
	if ((*exp)->prev)
		type = more_types(exp, len);
	return (type);
}


//Hem de separar per <, >, | i despres dir el tipus que toca de cada cosa. 
//Ho fem amb una matriu que contindra les paraules de cada costat
//la len de cada exp no cuenta el separador
void	exp_split_to_expand(t_tokens *tokens, t_expander **exp)
{
	int			flag;
	t_expander	*nodo;

	tokens->i_exp = 0;
	nodo = *exp;
	while (tokens->i_exp < (int)tokens->size)
	{
		flag = 0;
		nodo->len = len_to_expand(tokens, &flag) + flag;
		nodo->exp_matr = ft_calloc((size_t)(nodo->len + 1), sizeof(char *));
		fill_matrix_to_spand(tokens, &nodo, nodo->len, flag);
		(nodo)->exp_type = exp_type_to_expand(&nodo);
		if (tokens->i_exp < (int)tokens->size && !nodo->next)
		{
			create_node(&nodo);
			nodo = nodo->next;
			nodo->exp_type = 0;
		}
		tokens->i_exp++;
	}
}
