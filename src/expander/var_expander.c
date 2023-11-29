/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:08:31 by ojimenez          #+#    #+#             */
/*   Updated: 2023/11/29 17:21:41 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*allocate_str_expanded(t_tokens *tokens, int i)
{
	int		j;
	char	*str;

	i = 0;
	str = malloc((tokens->words[i].len) * sizeof(char));
	if (!str)
		exit(0);
	j = 1;
	while (j < tokens->words[i].len)
	{
		str[j - 1] = tokens->words[i].word[j];
		j++;
	}
	str[j - 1] = '\0';
	return (str);
}

void	replace_str_expanded(t_tokens *tokens, char *s_changed, int pos)
{
	int	len;
	int	i;

	len = ft_strlen(s_changed);
	i = 0;
	free(tokens->words[pos].word);
	tokens->words[pos].word = malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		tokens->words[pos].word[i] = s_changed[i];
		i++;
	}
	tokens->words[pos].word[i] = '\0';
	tokens->words[pos].len = len;
}

//Miramos las variables que tenemos que expandir
//Pregntar a anthony comillas simples y dobles si estan
void	exp_expand_var(t_tokens *tokens)
{
	int		i;
	char	*str;
	char	*s_changed;

	i = 0;
	while (i < tokens->size)
	{
		if (tokens->words[i].word[0] == '&' || (tokens->words[i].word[1] == '&'
				&& tokens->words[i].word[0] == '"'))
		{
			str = allocate_str_expanded(tokens, i);
			s_changed = getenv(str);
			if (s_changed != NULL)
				replace_str_expanded(tokens, s_changed, i);
			//si s_changed = NULL deixem la var amb el $ i si ho hem de mostrar fem un \n	
			free (str);
		}
		i++;
	}
}
