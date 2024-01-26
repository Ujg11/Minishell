/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:39:49 by ojimenez          #+#    #+#             */
/*   Updated: 2024/01/26 17:59:16 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_fork(pid_t *pid, t_expander *exp, t_executor *exec, t_env *env)
{
	*pid = fork();
	if (*pid == 0)
		child_process(exp, exec, env, exec->cmd_cont);
	close_fds(exp, exec);
	exec->cmd_cont++;
}

static int	init_command(t_expander *exp, t_executor *exec)
{
	t_expander	*node;
	int			error;

	node = exp;
	exec->ret_val = 0;
	exec->err_flag = 0;
	error = 0;
	while (node && (exec->redirection[0] == 0 || exec->redirection[1] == 0))
	{
		if (node->exp_type == INP || node->exp_type == INP_FD)
			error = redirect_input(node->next->exp_matr[0], exec, node);
		else if (node->exp_type == OUTP || node->exp_type == APPEND)
			error = redirect_output(node->next->exp_matr[0],
					node, exec, -1);
		else if (node->exp_type == OUTP_FD || node->exp_type == APPEND_FD)
			error = redirect_output(node->next->exp_matr[0], node,
					exec, -1);
		node = node->next;
	}
	if (exp->exp_type == HEREDOC || exp->exp_type == HEREDOC_PIPE)
		error = redirect_heredoc(get_heredoc_fd(exp), exec);
	return (error);
}

//Hace el init_command donde se inicializan y se hacen las redir
//Si hay tuberias y no hemos executado tantas, se crea una nueva
//Si no es un comando creado o lo
//es pero hay pipes,se crea un nuevo proceso
static void	init_exec(t_expander *exp, t_executor *exec, pid_t *pid, t_env *env)
{
	while (exp && exp->exp_matr)
	{
		if (init_command(exp, exec))
			exec->err_flag = 1;
		if (exec->num_pipes != 0 && exec->cmd_cont < exec->num_pipes
			&& !exec->err_flag)
			pipe(exec->pipe_fd);
		if ((our_cmd(exp->exp_matr[0]) || (!our_cmd(exp->exp_matr[0])
					&& exec->num_pipes != 0)) && exp->exp_type < FD)
		{
			do_fork(pid, exp, exec, env);
			if (exec->ret_val > 0)
				return ;
		}
		else
		{
			if (exp->exp_matr && exp->exp_type < FD)
			{
				exec->ret_val = command_done(exp, exec, env);
				exec->cmd_cont++;
			}
		}
		exp = exp->next;
	}
}

int	executor(t_expander *exp, t_env *env, t_tokens *t, t_executor *exec)
{
	pid_t		pid;
	t_expander	*node;

	exec->cmd_cont = 0;
	node = exp;
	exec->num_pipes = count_pipes(t);
	init_fd(&exec);
	if (heredoc(exp))
		exec->err_flag = 1;
	init_exec(node, exec, &pid, env);
	ft_wait(exec, pid);
	close_command(exec);
	return (exec->ret_val);
}
