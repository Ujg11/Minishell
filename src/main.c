/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2024/01/29 16:39:49 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	execute_command(CommandInfo *command, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(command->args[0], command->args, env) == -1)
		{
			perror("execve");
			printf("Error ejecutando el comando: %s\n", command->args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}*/

/*int	main(int argc, char *argv[], char *envp[])
{
	char	*input;

	signals();
	while (1)
	{
		input = readline(" > ");
		if (!input)
			exit(0);
		if (input)
		{
			printf("Texto ingresado: %s\n", input);
			// Inicializar tokens
			t_tokens	*tokens = init_token(NULL);
			// Parsear la entrada
			if (check_input(input))
			{
				// Error en la entrada
				printf("Error en la entrada.\n");
			} else {
				size_t i = 0;
				while (i < ft_strlen(input))
				{
					if (is_space(tokens, input + i)) {
						// Manejar espacios
						i += is_space(tokens, input + i);
					} else if (is_rd(input[i])) {
						// Manejar redirecciones
						// ...
					} else if (is_marks(tokens, input + i)) {
						// Manejar comillas
						i += is_marks(tokens, input + i);
					} else {
						i += string_tokens(tokens, input + i);
					}
					if (tokens->error == 1)
						break ;
				}
				if (!tokens->error)
				{
					// Ejecutar comandos según los tokens
					size_t j = 0;
					while (j < tokens->size)
					{
						t_word *current_word = &tokens->words[j];

						// Verificar si el token es un comando ejecutable
						if (current_word->type == 0) {
							// Obtener el nombre del comando
							char *command_name = current_word->word;
							// Ejecutar comandos específicos
							if (strcmp(command_name, "echo") == 0)
								echo(tokens->env);
							else if (strcmp(command_name, "pwd") == 0)
								pwd();
							else if (strcmp(command_name, "env") == 0)
								// Agregar lógica para el comando env
								// ...
							else
							{
								// Otros comandos
								printf("Comando desconocido: %s\n", command_name);
							}
						}
						j += 1;
					}
				}
			}
			// Liberar memoria de tokens
			free_tokens(tokens);
			free(input);
		}
	}
	return (0);
}*/

/*void	destroy_all(t_expander *exp, t_executor *exec)
{
	
}*/


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
	signals();
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
			
			t_expander *nodo;
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
			}
			if (exp->exp_matr[0])
			err = executor(exp, e, tokens, &exec);
			destroy_all(&tokens, &exp);
		}
		//else
		//	free(input);
	}
	
	//free_all();
}
