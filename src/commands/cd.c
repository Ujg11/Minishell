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

