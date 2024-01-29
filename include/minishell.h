/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:53:56 by agrimald          #+#    #+#             */
/*   Updated: 2024/01/29 19:49:22 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <signal.h>
# include <ctype.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>

struct	s_expander;

typedef struct s_word
{
	char		*word;
	size_t		len;
	int			type;
}	t_word;

typedef struct s_tokens
{
	t_word	*words;
	size_t	size;
	char	*str;
	char 	**env;
	int		error;
	int		i_exp;
}	t_tokens;

typedef struct s_env
{
	char	*key;
	char	*value;
	char	**env_cpy;	
}	t_env;

typedef struct s_pcs
{
	t_tokens	*argv;
	int			*types;
}t_pcs;

typedef struct s_expander
{
	int					exp_type;
	int					len;
	int					num_pipes;
	char				**exp_matr;
	char				*token;
	int					heredoc_fd;
	struct s_expander	*next;
	struct s_expander	*prev;
}	t_expander;

typedef struct s_executor
{
	int					pipe_fd[2];
	int					prev_pipe[2];
	int					fd_init[2];
	int					redirection[2];
	int					err_flag;
	int					ret_val;
	int					cmd_cont;
	int					num_pipes;
	t_env				*env;
	struct s_expander	*exp;
}	t_executor;
/*****************************************************
 *						UTILS						 *
 *****************************************************/

	/*--------ENV--------*/

size_t		read_variable(char *or_env);
void		duplicate_env(char **env_cpy, char *or_env);
char		*cpy_or_env(char *or_env);
//char		*ft_getenv_a(char *variable, char **env);

//destroy.c
void		destroy_expander(t_expander **exp);
void		destroy_all(t_tokens **t, t_expander **exp/*, t_executor **exec*/);


/*****************************************************
 *					  COMMANDS						 *
 *****************************************************/


	/*--------PWD--------*/
int			ft_pwd(void);

	/*--------ECHO-------*/
int			ft_echo(const char **args);

	/*---------CD--------*/
int			ft_cd(char **args);

	/*--------EXIT-------*/
int			ft_exit(char **argv, int len);

/*****************************************************
 *					  LEXER							 *
 *****************************************************/

	/*--------TOKENS_LEXER--------*/

/*bool	special_char(char corr);
size_t	get_char_special(char *token, char next_special_char);
char	get_next_char(char *token);
bool	search_char(char *token);*/

/*****************************************************
 *					  PARSER						 *
 *****************************************************/

	/*--------CHECK_ERRORS--------*/

/*int		is_rd(int c);
int		is_redirection(char *str, int i);
int		check_rd(char*str, int i);
int		check_input(char *str);*/

/*****************************************************
 *					  SIGNALS						 *
 *****************************************************/

void		signals(void);
void		signal_ctrl_c(int sig);

/*****************************************************
 *					  MAIN							 *
 *****************************************************/

//void		execute_command(CommandInfo *command);

/*****************************************************
 *					  PARSER 						 *
 *****************************************************/

	/*--------TOKEN_MANAGER--------*/

t_tokens	*init_token(char **env);
t_word		*create_word(char *str, size_t len, int type);
int			add_words(t_tokens *tokens, char *str, size_t len, int type);
int			matrixify(t_tokens *tokens);
void		free_tokens(t_tokens *tokens);

	/*--------CHECK_ERRORS--------*/

int			is_rd(int c);
int			is_redirection(char *str, int i);
int			check_rd(char *str, int i);
int			check_input(char *str);

	/*--------TOKEN_ANALYSIS--------*/

int			special_char(char c);
int			dst_dots(char *str, char dot);
int			is_marks(t_tokens *tokens, char *str);
int			is_space(t_tokens *tokens, char *str);

	/*--------TOKENS_OPERATIONS--------*/

void		print_wrd_format(char *format_str, t_word word);
void		print_tokens(t_tokens *tokens);
int			free_tokens_memory(t_tokens *tokens);

	/*--------PARSER--------*/

int			break_token(t_tokens *tokens, char *str);
int			is_normal_ch(char ch);
int			string_tokens(t_tokens *tokens, char *str);
int			parse_string(t_tokens *tokens, char *str);
int			parser(t_tokens **tokens, char *str, char **env);

	/*--------PROCESOS--------*/

void	print_pcs_recur(t_pcs *pcs, size_t index);
void	print(t_pcs *pcs);
void	print_pcs_types(t_tokens *tokens, int operator_types[]);

/*****************************************************
 *					  EXPANDER						 *
 *****************************************************/

//expander.c
t_expander	*expander(t_tokens *tokens, t_env *env, t_executor *exec);

//utils_exp.c
int			count_pipes(t_tokens *tokens);
int			len_to_expand(t_tokens *tokens, int *flag);
void		create_node(t_expander **nodo);
void		malloc_error(void);
char		*ft_expander_getenv(t_env *env, char *str);

//var_expander.c
void		exp_expand_var(t_tokens *tokens, t_env	*env, t_executor *exec);

//split_to_expand.c
void		exp_split_to_expand(t_tokens *tokens, t_expander **exp);

/*****************************************************
 *					  EXECUTOR						 *
 *****************************************************/

# define NONE 0
# define INP 1
# define OUTP 2
# define PIPE 3
# define HEREDOC 4
# define APPEND 5
# define INPIPE 6
# define OUTPIPE 7
# define HEREDOC_PIPE 8
# define APPEND_PIPE 9
# define FD 10
# define OUTP_FD 11
# define APPEND_FD 12
# define INP_FD 13

# define IN 0
# define OUT 1

//executor.c
int			executor(t_expander *exp, t_env *env, t_tokens *t,
				t_executor *exec);

//heredoc.c
int			heredoc(t_expander *exp);

//exec_utils.c
char		*get_filename(t_expander *exp);
int			ft_strcmp(char *s1, char *s2);
int			get_heredoc_fd(t_expander *exp);
void		close_fds(t_expander *exp, t_executor *exec);
void		ft_wait(t_executor *exec, pid_t pid);

//exec_redirections.c
int			redirect_input(char *filename, t_executor *exec, t_expander *exp);
int			redirect_output(char *filename, t_expander *exp,
				t_executor *exec, int fd);
int			redirect_heredoc(int fd, t_executor *exec);

//our_commands.c
int			our_cmd(char *command);
int			command_done(t_expander *exp, t_executor *exec, t_env *env);

//exec_execute.c
char		*ft_getenv(t_env *env, char	*str);
int			execute(t_expander *exp, t_executor *exec, t_env *env);
void		child_process(t_expander *exp, t_executor *exec, t_env *env, int c);

//exec_fds.c
void		close_command(t_executor *exec);
void		init_fd(t_executor *exec);

//test.c
int			count_pipes(t_tokens *tokens);

#endif
