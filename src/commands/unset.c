/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:52:41 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/01 18:52:42 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_unset(char *variable, t_env *env)
{
    int i = 0;
    char **env_ptr = env->env_cpy;

    while (env_ptr[i] != NULL)
    {
        if (strncmp(env_ptr[i], variable, strlen(variable)) == 0)
        {
            while (env_ptr[i] != NULL)
            {
                env_ptr[i] = env_ptr[i + 1];
                i++;
            }
            return (1);
        }
        i++;
    }
    return (0);
}