/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:20:28 by agrimald          #+#    #+#             */
/*   Updated: 2024/01/29 19:25:08 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/minishell.c"
#include "minishell.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	return (0);
}

/*int main(int argc, char **argv)
{
	(void)argv;
	if (argc == 2)
		pwd();
	return (0);
}*/
