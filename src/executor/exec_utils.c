/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:50:30 by ojimenez          #+#    #+#             */
/*   Updated: 2024/01/24 17:53:37 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

//Casos: INP, INPIPE, 
char	*get_filename(t_expander *exp)
{
	t_expander	*node;
	char		*filename;

	node = exp;
	filename = NULL;
	while (node && node->next)
	{
		if (node->token[0] == '<' || node->token[0] == '>')
		{
			if (node->next->exp_matr && node->next->exp_matr[0])
				filename = ft_strdup(node->next->exp_matr[0]);
			break ;
		}
		node = node->next;
	}
	return (filename);
}

int	get_heredoc_fd(t_expander *exp)
{
	int			heredoc_fd;
	t_expander	*node;

	node = exp;
	while (node->prev != NULL)
		node = node->prev;
	heredoc_fd = node->heredoc_fd;
	return (heredoc_fd);
}

void	ft_wait(t_executor *exec, pid_t pid)
{
	int	status;
	int	i;
	int	ret;

	i = 0;
	//printf("Cont = %d\n", exec->cmd_cont);
	while (exec->cmd_cont > i)
	{
		//printf("Entra 1\n");
		if (pid == wait(&status))
		{
			//printf("Entra 2\n");
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				//printf("Entra 3\n");
				if (WTERMSIG(status) == SIGINT)
					ret = 130;
				else if (WTERMSIG(status) == SIGQUIT)
				{
					printf("Quit: 3\n");
					ret = 131;
				}
			}
		}
		//printf("Surt 1\n");
		i++;
	}
	exec->ret_val = ret;
}

/*void	ft_wait(t_executor *exec, pid_t pid_pipe)
{
	int		i;
	int		status;
	int		real_status;
	pid_t	pid;

	i = -1;
	while (++i < exec->num_pipes)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == pid_pipe)
			real_status = status;
	}
	if (WIFEXITED(status))
		real_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			real_status = 130;
		else if (WTERMSIG(status) == SIGQUIT)
		{
			printf("Quit: 3\n");
			real_status = 131;
		}
	}
	exec->ret_val = real_status;
}*/

void	close_fds(t_expander *exp, t_executor *exec)
{
	if (exec->prev_pipe[IN] > 0)
	{
		close(exec->prev_pipe[IN]);
		close(exec->prev_pipe[OUT]);
	}
	if (exp->next != NULL)
	{
		exec->prev_pipe[IN] = exec->pipe_fd[IN];
		exec->prev_pipe[OUT] = exec->pipe_fd[OUT];
	}
	exec->redirection[IN] = 0;
	exec->redirection[OUT] = 0;
}
