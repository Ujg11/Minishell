/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:19:59 by agrimald          #+#    #+#             */
/*   Updated: 2024/01/27 11:53:04 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *count)
{
	int i = 0;

	while (count->env_cpy[i] != NULL)
	{
		printf("%s\n", count->env_cpy[i]);
		i++;
	}
}

void	hola(char **env, t_env *env_hola)
{
	int i = 0;
	int j = 0;

	while (env[i] != NULL)
		i++;
	env_hola->env_cpy = calloc(sizeof(char *), i + 1);
	if (!env_hola->env_cpy)
		exit(1);
	while (j < i)
	{
		env_hola->env_cpy[j] = strdup(env[j]);
		j++;
	}
	env_hola->env_cpy[j] = NULL;
}