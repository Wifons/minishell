/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:06:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/02 14:52:36 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>	 // a retirer
#include <stdbool.h> // a retirer

#include <fcntl.h>
#include <sys/wait.h>

#define PIPE_READ 0
#define PIPE_WRITE 1
#define CMD_NOT_FOUND 127
#define EXEC_ERROR 126
#define GENERAL_ERROR 1
#define SUCCESS 0
#define FILE_PERMS 0644

typedef enum
{
	WORD,
	L_REDIRECT,
	R_REDIRECT,
	HEREDOC,
	APP_REDIRECT,
	START_SUBSHELL,
	END_SUBSHELL,
	PIPE
} t_type;

typedef struct token
{
	char *value;
	t_type type;
	struct token *next;
} t_token;

typedef struct cmd
{
	char **arguments;
	char *l_redirect;
	char *r_redirect;
	char *app_redirect;
	char *heredoc_buff;
	int previous_pipe;
	int next_pipe;

	struct cmd *next;
} t_cmd;

typedef struct s_env_var
{
	char	*name;
	char	*value;
} t_env_var;

typedef struct	s_env_manager
{
	t_list	*vars;
	size_t	count;
} t_env_manager;

typedef struct s_shell
{
	t_env_manager	*env;
} t_shell;

/* Spliting*/
t_token *tokenize(char *str);
char *ft_clean_comment(char *str);
/*      Spliting Utils */
void _ft_free(char **result);
int is_quote(char *str, int i);
int check_in_quote(char *str, int i);
int check_symbol(char *str, int i);
int _ft_countword(char *str);
char *_ft_strcpy(char *src, char *dest, int debut, int fin);
char *extract_symbol_token(char *str, int *i);
t_token *create_token(void *content);
void ft_lstadd_backs(t_token **tokens, t_token *new);
void add_type(t_token *tokens);
t_type get_type(t_token *tokens);

int ft_count_quote(char *str);
int verif_input(char *str);
void ft_clean(t_token *tokens);

t_token *parse_line(char **str);
void print_tokens(t_token *tokens);
/* Verif error */
int parsing(t_token *tokens);
int verif_first_token(t_token *tokens);
int verif_other_tokens(t_token *tokens);
int verif_operator_utils(t_token *token);

/* Parsing cmd manager */
void init_cmd(t_cmd *cmd);
void add_arg(t_cmd *cmd, char *value);
void print_cmd(t_cmd *cmd);
void add_l_red(t_cmd *cmd, t_token **tokens);
void add_r_red(t_cmd *cmd, t_token **tokens);
void add_app_red(t_cmd *cmd, t_token **tokens);
void add_heredoc(t_cmd *cmd, t_token **tokens);
t_cmd *parse_cmd(t_token *tokens);
void ft_free_cmd_list(t_cmd *cmd);
void clear_quote(t_token *tokens);

/* Expansion */
void expansion(t_token *tokens);
char *expand_variable_w(char *value);
char *expand_variable_dq(char *value);

/* Execution */
int exec_single(t_shell *shell, t_cmd *cmd);
int exec_command(t_shell *shell, t_cmd *cmd);

/* -> Builtin */
int builtin_echo(t_cmd *cmd);
int builtin_export(t_shell *shell, char **args);
int builtin_cd(t_shell *shell, t_cmd *cmd);
int builtin_exit(t_shell *shell, char **args);
int	builtin_pwd(void);
int builtin_unset(t_shell *shell, char **args);
int	builtin_env(t_shell *shell, char **args);

int is_builtin(char *cmd);
int exec_builtin(t_shell *shell, t_cmd *cmd);

/* -> Redirections */
int open_infile(const char *file);
int open_outfile(const char *file, bool append);
int dup2_close(int fd, int target);
int setup_redirs(t_cmd *cmd);

/* -> Pipes */
int create_pipe(int pipefd[2]);
void close_pipe(int pipefd[2]);
int count_pipes(t_cmd *cmd);
void setup_pipe_in(int pipefd[2]);
void setup_pipe_out(int pipefd[2]);

/* -> External*/
char *find_cmd_path(const char *cmd);
int exec_external(t_shell *shell, t_cmd *cmd);
void print_cmd_not_found(const char *cmd);

/* -> Pipeline */
void exec_pipe_cmd(t_shell *shell, t_cmd *cmd, int in_fd, int pipefd[2]);
int exec_pipeline(t_shell *shell, t_cmd *cmd);

void	env_free(t_env_manager *env);
char	*env_get(t_env_manager *env, const char *name);
t_env_manager	*env_init(char **envp);
int	env_set(t_env_manager *env, const char *name, const char *val);
int	env_unset(t_env_manager *env, const char *name);
int	env_var_cmp_name(void *var_ptr, void *name_ref);
int	env_var_cmp_var(void *var1_ptr, void *var2_ptr);
void	env_var_free(void *var_ptr);
int	env_var_is_exportable(void *var_ptr);
char	**env_build_arr(t_env_manager *env);
char	*env_build_str(t_env_var *var);

int ft_strcmp(char *s1, char *s2);
void ft_free_array(char **array);
t_list	*ft_lstfind(t_list *lst, void *data_ref, int (*cmp)(void *, void *));
void	ft_lstsort(t_list **lst, int (*cmp)(void *, void *));
t_list	*ft_lstsort_dup(t_list *lst, int (*cmp)(void *, void *));
void	ft_lstdelone_if(t_list **lst, void *data_ref, int (*cmp)(void *, void *), void (*del)(void *));
void	ft_lstswap(t_list *a, t_list *b);
t_list	*ft_lstdup(t_list *lst);
int	ft_lstiter_ctx(t_list *lst, int (*f)(void *, void *), void *ctx);
int	ft_lstcount_if(t_list *lst, int (*f)(void *));

/* Heredoc test*/
int verif_heredoc(t_token *tokens);
int setup_heredoc(t_cmd *cmd);
char *remove_quotes(char *input);

#endif