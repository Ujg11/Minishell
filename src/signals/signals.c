/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:21:33 by agrimald          #+#    #+#             */
/*   Updated: 2024/01/27 18:41:22 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	signal_ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line(); // esto indica que el cursor debe moverse a una nueva linea;
	rl_replace_line("", 0); // reemplaza el antiguo texto con uno nuevo
	rl_redisplay(); // muestra lo escrito por la funcion anterior.
}


void	signals(void)
{
	//rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN); //esta linea maravillosa hace que le meta un null al readline y al hacer un ctrl-D, le mete ese null dentro del readline y hace un exit(1);
	signal(SIGINT, signal_ctrl_c);
}*/
