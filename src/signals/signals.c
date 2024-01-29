/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:21:33 by agrimald          #+#    #+#             */
/*   Updated: 2024/01/29 18:11:42 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	signal_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0); // reemplaza el antiguo texto con uno nuevo
		rl_on_new_line(); // esto indica que el cursor debe moverse a una nueva linea;
		rl_redisplay(); // muestra lo escrito por la funcion anterior.
	}
}

void	signals(void)
{
	//rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_ctrl_c);
}*/
