/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/08 19:32:07 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_space_main(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	init_minishell(t_tokens	*t, t_executor *exec, t_env *e)
{
	int			err;
	char		*input;
	t_expander	*exp;

	while (1)
	{
		input = readline("minishell-> ");
		if (!input)
			exit(1);
		if (input[0] != '\0' && is_space_main(input))
		{
			err = parser(&t, input, e->env_cpy);
			exp = expander(t, e, exec);
			if (err == 0)
			{
				if (exp->exp_matr[0])
					err = executor(exp, e, t, exec);
				destroy_all(&t, &exp);
			}
			free(input);
		}
		else
			free(input);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_tokens	*tokens;
	t_executor	exec;
	t_env		*e;

	(void)argc;
	(void)argv;
	tokens = NULL;
	e = malloc(sizeof(t_env));
	e->env_cpy = env;
	exec.env = e;
	exec.ret_val = 0;
	signals();
	init_minishell(tokens, &exec, e);
}

/*t_expander *nodo;
				nodo = exp;
				int i = 1;
				int j = 0;
					
				while (nodo)
				{
					printf("Nodo %d:\nTipo:%d\nLen = %d\n", i, nodo->exp_type, nodo->len);
					while (j < nodo->len + 1)
					{
						printf("%s\n", nodo->exp_matr[j]);
						j++;
					}
					printf("Token = %s\n", nodo->token);
					j = 0;
					i++;
					nodo = nodo->next;
				}*/