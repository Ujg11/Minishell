/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:52:29 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/08 21:16:21 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mod_strcmp(char *cmd, char *env)
{
	int	i;

	i = 0;
	while (cmd[i] && env[i])
	{
		if (cmd[i] == '=' && env[i] == '=')
			return (TRUE);
		if (cmd[i] != env[i])
			return (FALSE);
		i++;
	}
	if (cmd[i] == '\0' && (env[i] == '\0' || env[i] == '='))
		return (TRUE);
	return (FALSE);
}

int	check_env_without_value(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	replace_value(char *cmd, t_env *env)
{
	int	i;

	i = 0;
	while (env->env_cpy[i] != NULL)
	{
		if (mod_strcmp(cmd, env->env_cpy[i]) == TRUE)
		{
			free(env->env_cpy[i]);
			env->env_cpy[i] = strdup(cmd);
			return ;
		}
		i++;
	}
	normal_export(cmd, env);
}

int	var_exist(char *cmd, t_env *env)
{
	int	i;

	i = 0;
	while (env->env_cpy[i] != NULL)
	{
		if (mod_strcmp(cmd, env->env_cpy[i]) == TRUE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
