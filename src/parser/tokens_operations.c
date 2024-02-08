/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:37:06 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/08 19:01:42 by agrimald         ###   ########.fr       */
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
    size_t i;

    // Liberar la memoria de cada palabra en tokens->words
    if (tokens->words)
    {
        for (i = 0; i < tokens->size; i++)
        {
            free(tokens->words[i].word);
        }
        free(tokens->words);
    }

    // Liberar la memoria de tokens->env
    if (tokens->env)
    {
        for (i = 0; i < tokens->size; i++)
        {
            free(tokens->env[i]);
        }
        free(tokens->env);
    }

    // Liberar la memoria de tokens->str
    if (tokens->str)
        free(tokens->str);

    // Liberar la memoria de tokens
    free(tokens);

    return 1;
}
