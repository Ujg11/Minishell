/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:16:10 by agrimald          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/09 13:59:45 by agrimald         ###   ########.fr       */
=======
/*   Updated: 2024/02/09 14:09:21 by ojimenez         ###   ########.fr       */
>>>>>>> 6326f127378060ab892f2b1540aa15f4779549a5
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_char(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	dst_dots(char *str, char dot)
{
	int	i;

	i = 1;
	if (str[1] == '\0')
	{
		printf("Error: hay null oe\n");
		return (-1);
	}
	if (str[1] == dot)
		return (-2);
	while (str[i] && str[i] != dot)
		i++;
	if (str[i] == '\0')
	{
		printf("Error: not closing marks\n");
		return (-1);
	}
	return (i - 1);
}

int	is_marks(t_tokens *tokens, char *str)
{
	int	len;

	if (str[0] == '"')
		len = dst_dots(str, str[0]);
	else
		len = ft_strlen(str);
	if (len == -1 || len == -2)
	{
		tokens->error = 1;
		return (1);
	}
	if (len == 0)
		return (len);
	if (str[0] == '"')
		add_words(tokens, str + 1, len, 2);
	//else if (str[0] == '\'')
		//add_words(tokens, str + 1, len, 2);
	else
		add_words(tokens, str, len, 0);
	return (len + 2);
}

int	is_space(t_tokens *tokens, char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	add_words(tokens, " ", 1, 4);
	return (i);
}

char	*delete_space(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] == ' ')
	{
		str[i] = '\0';
		i--;
	}
	return (str);
}
