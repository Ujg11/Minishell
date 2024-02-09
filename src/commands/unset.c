/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:52:41 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/09 16:40:12 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char *variable, t_env *env)
{
	char	**env_ptr;
	int		i;

	i = 0;
	env_ptr = env->env_cpy;
	while (env_ptr[i] != NULL)
	{
		if (ft_strncmp(env_ptr[i], variable, ft_strlen(variable)) == 0)
		{
			free(env_ptr[i]);
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


/*corregir este error 
minishell-> export PATH=/usr/local/bin:/bin:/usr/bin
minishell(4787,0x10e822dc0) malloc: *** error for object 0x7ffee6e69773: pointer being freed was not allocated
minishell(4787,0x10e822dc0) malloc: *** set a breakpoint in malloc_error_break to debug
[1]    4787 abort      ./minishell

y que tambien el unset de un mensaje de error al enviarle

unset $PATH
*/