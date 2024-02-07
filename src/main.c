/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/07 10:29:59 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	tokens = NULL;
	e = malloc(sizeof(t_env));
	e->env_cpy = env;
	exec.env = e;
	exec.ret_val = 0;
	while (1)
	{
		signals();
		input = readline(" > ");
		if (!input)
			exit(0);
		if (input[0] != '\0')
		{
			err = parser(&tokens, input, e->env_cpy);
			e->env_cpy = env;
			exp = expander(tokens, e, &exec);
			if (exp == NULL)
			{
				printf("Error aqui\n");
				continue;
			}
			if (err == 0)
			{
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
				if (exp->exp_matr[0])
					err = executor(exp, e, tokens, &exec);
				destroy_all(&tokens, &exp);
			}
		}
		else
			free(input);
	}
}
