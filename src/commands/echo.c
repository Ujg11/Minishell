/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:42:36 by agrimald          #+#    #+#             */
/*   Updated: 2024/01/29 21:03:26 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	ft_echo(char **args)
{
	bool	print_line;

	print_line = true;
	if (ft_strncmp(*args, "echo", ft_strlen(*args)) != 0)
		return (EXIT_FAILURE);
	args++;
	if (*args && ft_strncmp(*args, "-n", ft_strlen("-n") + 1) == 0)
	{
		print_line = false;
		args++;
	}
	while (*args != NULL)
	{
		printf("%s", *args);
		args++;
		if (*args != NULL)
			printf(" ");
	}
	if (print_line)
		printf("\n");
	return (EXIT_SUCCESS);
}*/

int ft_echo(const char **args)
{
	    bool print_line = true;
    args++; // Avanzar al primer argumento después de "echo"
    if (*args && strncmp(*args, "-n", strlen("-n") + 1) == 0)
    {
        print_line = false;
        args++;
    }
    while (*args != NULL)
    {
        const char *arg = *args;
        size_t arg_len = strlen(arg);
        if (arg_len >= 2 && ((arg[0] == '"' && arg[arg_len - 1] == '"') || (arg[0] == '\'' && arg[arg_len - 1] == '\'')))
        {
            // Si la cadena comienza y termina con comillas simples o dobles, imprímela sin las comillas
            printf("%.*s", (int)arg_len - 2, arg + 1);
        }
        else
        {
            // Si no, imprimir la cadena normalmente
            // Eliminar comillas dentro de la cadena
            const char *quote = strpbrk(arg, "\"\'");
            while (quote != NULL)
            {
                size_t chunk_len = quote - arg;
                printf("%.*s", (int)chunk_len, arg);
                arg = quote + 1; // Saltar la comilla encontrada
                quote = strpbrk(arg, "\"\'");
            }
            // Imprimir el resto de la cadena
            printf("%s", arg);
        }
        args++;
        if (*args != NULL)
            printf(" ");
    }
    if (print_line)
        printf("\n");
    return (0);
}
