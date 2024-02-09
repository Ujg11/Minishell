/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:25:59 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/09 14:12:24 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	break_token(t_tokens *tokens, char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
	{
		add_words(tokens, str, 2, 5);
		return (2);
	}
	add_words(tokens, str, 1, 3);
	return (1);
}

int	is_normal_ch(char ch)
{
	if (special_char(ch) || ch == '#' || ch == '"' \
			|| ch == ' ' || ch == '\'')
		return (1);
	return (0);
}

int	string_tokens(t_tokens *tokens, char *str)
{
	int	i;
	int	command_found;

	i = 0;
	command_found = 0;
	while (str[i] && !is_normal_ch(str[i]))
		i++;
	if (!command_found)
	{
		if (i >= 2 && str[0] == '$' && str[1] == '?' && is_normal_ch(str[i]))
			add_words(tokens, str, i, 0);
		else
			add_words(tokens, str, i, 0);
	}
	return (i);
}

int	parse_string(t_tokens *tokens, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '#')
	{
		if (special_char(str[i]))
			i += break_token(tokens, str + i);
		else if (str[i] == '"' || str[i] == '\'')
			i += is_marks(tokens, str + i);
		else if (str[i] == ' ')
			i += is_space(tokens, str + i);
		else
			i += string_tokens(tokens, str + i);
		if (tokens->error == 1)
			return (1);
		j++;
	}
	return (0);
}

int	parser(t_tokens **tokens, char *str, char **env)
{
	str = delete_space(str);
	if (!*tokens)
	{
		*tokens = init_token(env);
		if (!*tokens)
		{
			printf("Error: oe tu token no funciona\n");
			return (1);
		}
	}
	(*tokens)->env = env;
	(*tokens)->error = 0;
	if (check_input(str))
		return (42);
	parse_string(*tokens, str);
	matrixify(*tokens);
	if ((*tokens)->error == 0)
		add_history(str);
	return ((*tokens)->error);
}
