/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2024/01/29 19:08:45 by ojimenez         ###   ########.fr       */
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
	//signals();
	while (1)
	{
		input = readline(" > ");
		if (!input)
			exit(0);
		if (input[0] != '\0')
		{
			ft_exit(input);
			err = parser(&tokens, input, e->env_cpy);
			e->env_cpy = env;
			exp = expander(tokens, e, &exec);
			
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
		else
			free(input);
	}
}
