/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:06:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/27 21:53:21 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h> // a retirer
# include <stdbool.h> // a retirer

#include <fcntl.h>
#include <sys/wait.h>

#define PIPE_READ  0
#define PIPE_WRITE 1
#define CMD_NOT_FOUND 127
#define EXEC_ERROR 126
#define GENERAL_ERROR 1
#define SUCCESS 0
#define FILE_PERMS 0644

/* File descriptor constants */
# define FD_ERR				-1
# define NO_PIPE			-1
# define RD					0
# define WR					1
# define PIPE_ERR			-1

/* File permissions */
# define FILE_PERM			0644

/* Error codes */
# define ERR_NULL_CMD		-2
# define ERR_NO_ARGS		-3
# define ERR_DUP_IN			-4
# define ERR_DUP_OUT		-5
# define ERR_SAVE_FDS		-6
# define ERR_NOT_BUILTIN	-7
# define ERR_CMD_NOT_FOUND	-8
# define ERR_PIPE_CREATE	-9
# define ERR_DUP_PIPE_IN	-10
# define ERR_DUP_PIPE_OUT	-11
# define ERR_OPEN_IN		-12
# define ERR_OPEN_OUT		-13
# define ERR_UNKNOWN_REDIR	-16
# define ERR_FD_OP			-17

typedef enum 
{
    WORD,           // 0
    SINGLEQUOTE,    // 1
    DOUBLEQUOTE,    // 2
    L_REDIRECT,     // 3
    R_REDIRECT,     //4
    HEREDOC,        //5
    APP_REDIRECT,   //6
    START_SUBSHELL, //7
    END_SUBSHELL,   //8
    PIPE            //9
} t_type;

typedef struct token
{
    char    *value;
    t_type  type;
    struct token *next;
}	t_token;

typedef struct cmd
{
    char    **arguments;
    char    *l_redirect;
    char    *r_redirect;
    char    *app_redirect;
		char		*heredoc_delimiter;
    int     previous_pipe;
    int     next_pipe;

    struct cmd *next;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	int		last_exit_status;
}	t_shell;

/* Spliting*/
t_token *tokenize(char *str);
char    *ft_clean_comment(char *str);
/*      Spliting Utils */
void	_ft_free(char **result);
int		is_quote(char *str, int i);
int		check_in_quote(char *str, int i);
int		check_symbol(char *str, int i);
int		_ft_countword(char *str);
char	*_ft_strcpy(char *src, char *dest, int debut, int fin);
char	*extract_symbol_token(char *str, int *i);
t_token	*create_token(void *content);
void	ft_lstadd_backs(t_token **tokens, t_token *new);
void	add_type(t_token *tokens);
t_type	get_type(t_token *tokens);

int	ft_count_quote(char *str);
int verif_input(char *str);
void	ft_clean(t_token *tokens);

t_token	*parse_line(char **str);
void	print_tokens(t_token *tokens);
/* Verif error */
int parsing(t_token *tokens);
int verif_first_token(t_token *tokens);
int verif_other_tokens(t_token *tokens);
int verif_operator_utils(t_token *token);

/* Parsing cmd manager */
void    init_cmd(t_cmd *cmd);
void    add_arg(t_cmd *cmd, char *value);
void print_cmd(t_cmd *cmd);
void	add_l_red(t_cmd *cmd, t_token **tokens);
void	add_r_red(t_cmd *cmd, t_token **tokens);
void	add_app_red(t_cmd *cmd, t_token **tokens);
t_cmd   *parse_cmd(t_token *tokens);
void print_cmd(t_cmd *cmd); // a retirer juste pour print 
void	clear_quote(t_token *tokens);

/* Expansion */
void    expansion(t_token *tokens);
char    *expand_variable_w(char *value);
char    *expand_variable_dq(char *value);

/* Execution */
int		exec_single(t_shell *shell, t_cmd *cmd);
int		exec_command(t_shell *shell, t_cmd *cmd);

/* -> Builtin */
int		builtin_echo(t_shell *shell, t_cmd *cmd);
int		builtin_cd(t_shell *shell, t_cmd *cmd);
int		is_builtin(char *cmd);
int		exec_builtin(t_shell *shell, t_cmd *cmd);

/* -> Redirections */
int		open_infile(const char *file);
int		open_outfile(const char *file, bool append);
int		dup2_close(int fd, int target);
int		setup_redirs(t_cmd *cmd);

int		setup_heredoc(t_cmd *cmd);
// int		create_heredoc_pipe(char *delimiter);

/* -> Pipes */
int		create_pipe(int pipefd[2]);
void	close_pipe(int pipefd[2]);
int		count_pipes(t_cmd *cmd);
void	setup_pipe_in(int *in_fd, int pipefd[2]);
void	setup_pipe_out(int pipefd[2]);

/* -> External*/
char	*find_cmd_path(const char *cmd);
int		exec_external(t_shell *shell, t_cmd *cmd);
void	print_cmd_not_found(const char *cmd);

/* -> Pipeline */
void	exec_pipe_cmd(t_shell *shell, t_cmd *cmd, int in_fd, int pipefd[2]);
int		exec_pipeline(t_shell *shell, t_cmd *cmd);

/* -> Utils */
void	ft_free_array(char **array);
int		ft_strcmp(char *s1, char *s2);

int		count_env_vars(char **env);
int		find_env_var(t_shell *shell, char *name);
char	*create_env_var(char *name, char *value);
char	**resize_env(t_shell *shell, int new_size);

// Environment operations
char	*get_env_value(t_shell *shell, char *name);
int		set_env_value(t_shell *shell, char *name, char *value);

// Environment lifecycle
int		init_env(t_shell *shell, char **envp);
void	cleanup_env(t_shell *shell);

// Environment builtins
int		builtin_env(t_shell *shell, t_cmd *cmd);
int		builtin_export(t_shell *shell, t_cmd *cmd);

// extern char	**environ;

#endif