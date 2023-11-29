/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:37:06 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/28 11:18:56 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_wrd_format(char *format_str, t_word word)
{
	if (!format_str)
		printf("{%d}%s<", word.type, word.word);
	else
		printf(format_str, word.type, word.word);
}

void	print_tokens(t_tokens *tokens)
{
	size_t	i;

	i = 0;
	while (i < tokens->size)
	{
		print_wrd_format("%d: >>%s<<\n", tokens->words[i]);
		i += 1;
	}
}

int	free_tokens_memory(t_tokens *tokens)
{
	size_t	i;
	//t_word	*word; este no vale
	t_word	*aux; 

	i = 0;
	//word = tokens->words; este tampoco vale
	while (tokens->words)
	{
		aux = tokens->words;
		free(tokens->words);
		//free(word); este tampoco vale
		tokens->words = NULL;
		//word = aux; este tampoco vale
	}
	if (tokens->words)
		free(tokens->words);
	//free(word); este tampoco vale
	return (1);
}
