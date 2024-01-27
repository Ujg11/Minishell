/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:43:15 by agrimald          #+#    #+#             */
/*   Updated: 2024/01/27 12:08:54 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*init_token(t_env **env)
{
	t_tokens	*tokens;

	tokens = malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->words = NULL;
	tokens->size = 0;
	tokens->env = env;
	return (tokens);
}

int	add_words(t_tokens *tokens, char *str, size_t len, int type)
{
	t_word *new_word = create_word(str, len, type);
	if (!new_word)
		return (0);
	tokens->size += 1;
	t_word *new_array = calloc(tokens->size, sizeof(t_word));
	if (!new_array)
	{
		free(new_word->word);
		free(new_word);
		return (0);
	}
	if (tokens->size > 1)
	{
		memcpy(new_array, tokens->words, (tokens->size - 1) * sizeof(t_word));
		free(tokens->words);
	}
	new_array[tokens->size - 1] = *new_word;
	tokens->words = new_array;
	free(new_word);
	return (1);
}

void	free_tokens(t_tokens *tokens)
{
	if (tokens)
	{
		free(tokens->words);
		free(tokens);
	}
}

int matrixify(t_tokens *tokens) 
{
	t_word *word;
	size_t i;

	word = tokens->words;
	if (!word)
		return 0;

	tokens->env = (char **)calloc(tokens->size + 1, sizeof(char *));
	if (!tokens->env)
		return 0;

	i = 0;
	while (i < tokens->size)
	{
		tokens->env[i] = ft_strdup(word[i].word);
		if (!tokens->env[i])
			return 0;
		/*memcpy(tokens->env[i]->env_cpy, word[i].word, word[i].len);
		tokens->env[i]->env_cpy[word[i].len] = '\0';*/
		i++;
	}
	return (1);
}

/*int	matrixify(t_tokens *tokens)
{
	t_word	*word;
	size_t	i;

	word = tokens->words;
	if (!word)
		return (0);
	//word = tokens->words;
	word->env = (t_env **)ft_calloc(tokens->size + 1, sizeof(t_env *));
	if (!tokens->env)
		return (0);
	//word = tokens->words;
	i = 0;
	while (i < tokens->size)
	{
		tokens->env[i] = (t_env *)ft_calloc(1, sizeof(t_env));
		if (!tokens->env[i])
			return (0);
		ft_memcpy(word->word[i], word[i].word, word->len);
		word->word[i][word->len] = '\0';
		//word->word[i] = word;
		//word = word + 1;
		i++;
	}
	return (1);
}*/

/*int main()
{
	t_tokens *tokens = init_token(NULL);

	add_words(tokens, "Hello World", 5, 0);
	add_words(tokens, "World Hello", 5, 1);

	size_t i = 0;
	while (i < tokens->size)
	{
		printf("%s\n", tokens->words[i].word);
		i++;
	}
	free_tokens(tokens);
	return (0);
}*/
