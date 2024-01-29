/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:49:49 by ojimenez          #+#    #+#             */
/*   Updated: 2024/01/29 17:18:38 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	our_cmd(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		command[i] = ft_tolower(command[i]);
		i++;
	}
	if (!ft_strcmp(command, "echo"))
		return (0);
	else if (!ft_strcmp(command, "cd"))
		return (0);
	else if (!ft_strcmp(command, "pwd"))
		return (0);
	else if (!ft_strcmp(command, "export"))
		return (0);
	else if (!ft_strcmp(command, "unset"))
		return (0);
	else if (!ft_strcmp(command, "env"))
		return (0);
	else if (!ft_strcmp(command, "exit"))
		return (0);
	return (1);
}

static void	pass_tolower(t_expander *exp)
{
	int	i;

	i = 0;
	while (exp->exp_matr[0][i] != '\0')
	{
		ft_tolower(exp->exp_matr[0][i]);
		i++;
	}
}

/****  FALTA RELLENAR LAS FUNCIONES CON SUS PARAMETROS  ****/
int	command_done(t_expander *exp, t_executor *exec, t_env *env)
{
	exec->redirection[IN] = 0;
	exec->redirection[OUT] = 0;
	pass_tolower(exp);
	env->env_cpy[0] = env->env_cpy[0] + 1 - 1;
	/*if (!ft_strcmp(exp->exp_matr[0], "echo"))
		return (ft_echo());*/
	if (!ft_strcmp(exp->exp_matr[0], "cd"))
		return (ft_cd(exp->exp_matr));
	/*else if (!ft_strcmp(exp->exp_matr[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(exp->exp_matr[0], "export"))
		return (ft_export());
	else if (!ft_strcmp(exp->exp_matr[0], "unset"))
		return (ft_unset());
	else if (!ft_strcmp(exp->exp_matr[0], "env"))
		return (ft_env());*/
	//else if (!ft_strcmp(exp->exp_matr[0], "exit"))
	//	return (ft_exit(exp->exp_matr[0]));
	return (127);
}






























