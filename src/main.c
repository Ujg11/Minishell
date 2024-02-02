/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/02 17:33:54 by agrimald         ###   ########.fr       */
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
			//ft_exit(input);
			err = parser(&tokens, input, e->env_cpy);
			//print_tokens(tokens);
			e->env_cpy = env;
			exp = expander(tokens, e, &exec);
			if (exp == NULL)
			{
				printf("Error aqui\n");
				continue;
			}
			printf("ERROR = %d\n", err);
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
