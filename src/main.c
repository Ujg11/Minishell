/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/08 17:33:16 by agrimald         ###   ########.fr       */
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

int	main(int argc, char *argv[], char *env[])
{
	char		*input;
	t_tokens	*tokens;
	t_expander	*exp;
	t_executor	exec;
	t_env		*e;
	int			err;

	(void)argc;
	(void)argv;
	//(void)env;//NO
	input = NULL;
	tokens = NULL;
	e = malloc(sizeof(t_env));
	e->env_cpy = env;
	exec.env = e;
	exec.ret_val = 0;
	signals();
	while (1)
	{
		input = readline("minishell-> ");
		if (!input)
			exit(1);
		if (input[0] != '\0' && is_space_main(input))
		{
			err = parser(&tokens, input, e->env_cpy);
			exp = expander(tokens, e, &exec);
			if (exp == NULL)
			{
				printf("Error aqui\n");
				continue ;
			}
			if (err == 0)
			{
				if (exp->exp_matr[0])
					err = executor(exp, e, tokens, &exec);
				destroy_all(&tokens, &exp);
			}
			free(input);
		}
		else
			free(input);
	}
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