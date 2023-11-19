/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:51:53 by ojimenez          #+#    #+#             */
/*   Updated: 2023/11/17 16:58:57 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//usar chdir para movernos entre directorios
//idea: podemos distinguir entre el caso de que sea para delante o para atras. Si es para delante
//podemos poner en el path lo que el usuario escriba para ir a los siguientes directorios. Si es 
//para atras podemos obtener el path con getcwd y quitarle info

char	*ft_strcat(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = s1;
	while (s1[i])
		i++;
	str[i] = '/'; //o al reves
	i++;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++; 
	}
	str[i] = '\0';
	return (str);
}

//Caso de ir hacia delante
int	cd(char **args)
{
	int		flag;
	char	*pwd_i;
	char	*pwd_f;

	print_line = 1;
	if (ft_strncmp(*args, "cd", ft_strlen(*args)) != 0)
		return (EXIT_FAILURE);
	args++;
	pwd_i = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("get_cwd");
		exit(EXIT_FAILURE);
	}
	pwd_f = malloc((ft_strlen(pwd_i) + ft_strlen(*args)) * sizeof(char));
	pwd_f = ft_strcat(pwd_i, *args);
	free (pwd_i);
	flag = chdir(pwd_f);
	if (flag == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}