/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:19:59 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/07 18:39:41 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *count)
{
	int i = -1;

	while (count->env_cpy[++i] != NULL)
	{
		if (check_env_without_value(count->env_cpy[i]) == 0)
			continue;
		printf("%s\n", count->env_cpy[i]);
	}
	return (0);
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