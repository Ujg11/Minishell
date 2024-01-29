/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:14:52 by agrimald          #+#    #+#             */
/*   Updated: 2024/01/27 12:53:23 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_rd(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_redirection(char *str, int i)
{
	if (str[i + 1] == '\0')
		return (1);
	if (i < 2)
		return (0);
	if (is_rd(str[i - 1]) && is_rd(str[i - 2]) && is_rd(str[i]))
		return (1);
	if (str[i] == '<' && str[i - 1] == '>')
		return (1);
	return (0);
}

int	check_rd(char *str, int i)
{
	if (str[i] == '<' || str[i] == '>')
		return (1);
	if (str[i + 1] == '\0')
		return (1);
	if (str[i - 1] == '<' || str[i - 1] == '>')
		return (1);
	return (0);
}

int	check_input(char *str)
{
	if (str == NULL || *str == '\0')
		return (1);
	while (*str)
	{
		if ((*str == '>' || *str == '<' || *str == '|') && 
			(str[1] == '>' || str[1] == '<' || str[1] == '|' || str[1] == '\0'))
		{
			printf("syntax error near unexpected token `%c%c'\n", *str, str[1]);
			return (1);
		}
		else if (*str == '|' && (str[1] == '|' || str[1] == '>' || str[1] == '<'))
		{
			printf("syntax error near unexpected token `%c%c'\n", *str, str[1]);
			return (1);
		}
		else if ((*str == '>' || *str == '<' || *str == '|') && str[1] == '\0')
		{
			printf("syntax error near unexpected token `%c'\n", *str);
			return (1);
		}
		str++;
	}
	if (*(str - 1) == '\n')
	{
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

/*int main() 
{
    char str[] = "ls >output.txt|grep pattern";
    int result = check_input(str);

    if (result == 0) 
	{
        printf("No hay errores de sintaxis en la cadena.\n");
    }
   	else
   	{
        printf("Se encontraron errores de sintaxis en la cadena.\n");
    }
    return 0;
}*/
