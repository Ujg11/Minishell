/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:48:23 by ojimenez          #+#    #+#             */
/*   Updated: 2024/02/07 10:53:46 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_command(t_executor *exec)
{
	dup2(exec->fd_init[IN], STDIN_FILENO);
	dup2(exec->fd_init[OUT], STDOUT_FILENO);
	close(exec->fd_init[IN]);
	close(exec->fd_init[OUT]);
}

void	init_fd(t_executor *exec)
{
	exec->pipe_fd[IN] = -1;
	exec->pipe_fd[OUT] = -1;
	exec->prev_pipe[IN] = -1;
	exec->prev_pipe[OUT] = -1;
	exec->fd_init[IN] = dup(STDIN_FILENO);
	exec->fd_init[OUT] = dup(STDOUT_FILENO);
	exec->redirection[IN] = 0;
	exec->redirection[OUT] = 0;
}


// Código simplificado para ilustrar la idea
int execute_pipeline(char *commands[], int num_commands, char *output_file) {
    int pipefd[2];
    int input_fd = STDIN_FILENO;

    for (int i = 0; i < num_commands; i++) {
        if (pipe(pipefd) == -1) {
            perror("pipe");
            return 1;
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {  // Proceso hijo
            close(pipefd[0]);  // Cerramos el extremo de lectura del pipe
            dup2(input_fd, STDIN_FILENO);  // Redirigir entrada desde el descriptor anterior
            close(input_fd);

            if (i == num_commands - 1) {
                // Último comando, redirigir salida al archivo
                int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            } else {
                // No es el último comando, redirigir salida al pipe
                dup2(pipefd[1], STDOUT_FILENO);
            }

            execvp(commands[i], &commands[i]);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {  // Proceso padre
            close(pipefd[1]);  // Cerramos el extremo de escritura del pipe
            input_fd = pipefd[0];  // Actualizamos el descriptor de entrada para el próximo comando
            waitpid(pid, NULL, 0);  // Esperar a que el hijo termine
        }
    }

    return 0;
}
