/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:08:43 by ojimenez          #+#    #+#             */
/*   Updated: 2024/01/22 15:03:28 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp_hd(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static int	init_heredoc(t_expander *exp, char *str)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	else
	{
		while (42)
		{
			signals();
			line = readline("> ");
			if (ft_strcmp_hd(line, str) == 0)
				break ;
			write(fd[OUT], line, ft_strlen(line));
			free(line);
		}
	}
	close(fd[OUT]);
	exp->heredoc_fd = fd[IN];
	return (0);
}

int	heredoc(t_expander *exp)
{
	t_expander	*node;

	node = exp;
	while (node != NULL)
	{
		if (node->exp_type == HEREDOC || node->exp_type == HEREDOC_PIPE)
		{
			if (init_heredoc(node, node->next->exp_matr[0]))
				return (1);
		}
		node = node->next;
	}
	return (0);
}
