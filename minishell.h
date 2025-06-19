/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:06:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/19 19:29:01 by wifons           ###   ########.fr       */
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
# include <string.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

# define PIPE_READ 0
# define PIPE_WRITE 1
# define CMD_NOT_FOUND 127
# define EXEC_ERROR 126
# define GENERAL_ERROR 1
# define SUCCESS 0
# define FILE_PERMS 0644

typedef enum s_type
{
	WORD,
	L_REDIRECT,
	R_REDIRECT,
	HEREDOC,
	APP_REDIRECT,
	START_SUBSHELL,
	END_SUBSHELL,
	PIPE
}	t_type;

typedef struct token
{
	char			*value;
	t_type			type;
	struct token	*next;
}	t_token;

typedef struct s_redir_ordered
{
	int						redirect;
	int						append;
	char					*filename;
	struct s_redir_ordered	*next;
}	t_redir_ordered;

typedef struct cmd
{
	char			**arguments;
	char			*l_redirect;
	char			*r_redirect;
	char			*app_redirect;
	char			*heredoc_buff;
	t_redir_ordered	*redir_list;
	int				previous_pipe;
	int				next_pipe;
	struct cmd		*next;
}	t_cmd;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_shell
{
	t_env_var	*env;
	int			global_status;
	int			should_exit;
	int			curr_line;
}	t_shell;

typedef struct s_parse_cmd
{
	t_cmd	**cmd;
	t_cmd	**head_cmd;
	t_token	**tmp;
	t_token	*tokens;
	t_shell	*shell;
}	t_parse_cmd;

void		ft_free_token_list(t_token *tokens);
void		append_cmd(t_cmd **head, t_cmd *new_cmd);

/* Spliting*/
t_token		*tokenize(t_shell *shell, char *str);
char		*ft_clean_comment(char *str);

/*  Spliting Utils */
void		ft_free(char **result);
int			is_quote(char *str, int i);
int			check_in_quote(char *str, int i);
int			check_symbol(char *str, int i);
int			ft_countword_ms(char *str);
int			count_symbol_token(char *str, int *i);
int			checking_char(char *str, int *i, int *in_word);
char		*_ft_strcpy(char *src, char *dest, int debut, int fin);
char		*extract_symbol_token(char *str, int *i);
t_token		*create_token(void *content);
void		ft_lstadd_backs(t_token **tokens, t_token *new);
void		add_type(t_token *tokens);
t_type		get_type(t_token *tokens);

int			ft_count_quote(t_shell *shell, char *str);
int			verif_input(t_shell *shell, char *str);
void		ft_clean(t_token *tokens);

t_token		*parse_line(t_shell *shell, char **str);

/* Verif error */
int			parsing(t_shell *shell, t_token *tokens);
int			verif_first_token(t_shell *shell, t_token *tokens);
int			verif_other_tokens(t_shell *shell, t_token *tokens);
int			verif_operator_utils(t_shell *shell, t_token *token);
int			syntax_error(t_shell *shell, const char *value);

/* Parsing cmd manager */
void		init_cmd(t_cmd *cmd);
void		add_arg(t_cmd *cmd, char *value);
void		print_cmd(t_cmd *cmd);
void		add_l_red(t_cmd *cmd, t_token **tokens);
void		add_r_red(t_cmd *cmd, t_token **tokens);
void		add_app_red(t_cmd *cmd, t_token **tokens);
void		add_heredoc(t_cmd *cmd, t_token **tokens);
t_cmd		*parse_cmd(t_token *tokens, t_shell *shell);
int			init_parse_struct(t_parse_cmd *parse, t_token *tokens,
				t_shell *shell);
void		ft_free_cmd_list(t_cmd *cmd);
t_cmd		*ft_free_parse_cmd(t_parse_cmd *parse, t_cmd *result);
int			error_parse(t_cmd **head_cmd, t_token *tokens, t_shell *shell);
void		clear_quote(t_token *tokens);

/* Expansion */
void		expansion(t_shell *shell, t_token *tokens);
void		expand_brace(t_shell *shell, const char *value,
				char **exp, int *skip);
void		expand_simple(t_shell *shell, const char *value,
				char **exp, int *skip);
char		*expand_var(t_shell *shell, char *value);
char		*expand_cmd_code(t_shell *shell, char *value);
char		*replace_cmd_code(char *value, char *code);
char		*ft_strjoin_free(char *s1, const char *s2);
char		*translation(char *value);
char		*ft_strjoin_free(char *s1, const char *s2);

/* Execution */
int			exec_single(t_shell *shell, t_cmd *cmd);
int			exec_command(t_shell *shell, t_cmd *cmd);
int			check_all_redirs(t_redir_ordered *redir);

/* -> Builtin */
int			builtin_echo(t_cmd *cmd);
int			builtin_export(t_shell *shell, char **args);
void		print_declared_var(void *data);
int			print_all_vars(t_env_var *env);
int			builtin_cd(t_shell *shell, t_cmd *cmd);
int			builtin_exit(t_shell *shell, t_cmd *cmd);
int			is_option(char *arg);
int			legal_number(char *string, long *result);
int			builtin_pwd(t_shell *shell, char **arguments);
int			builtin_unset(t_shell *shell, char **args);
int			builtin_env(t_shell *shell, char **args);
int			is_builtin(char *cmd);
int			exec_builtin(t_shell *shell, t_cmd *cmd);

/* -> Redirections */
int			open_infile(const char *file);
int			open_outfile(const char *file, bool append);
int			dup2_close(int fd, int target);
int			setup_redirs(t_cmd *cmd);

/* -> Pipes */
int			create_pipe(int pipefd[2]);
void		close_pipe(int pipefd[2]);
int			count_pipes(t_cmd *cmd);
void		setup_pipe_in(int pipefd[2]);
void		setup_pipe_out(int pipefd[2]);

/* -> External*/
char		*find_cmd_path(t_env_var *env, const char *cmd);
int			exec_external(t_shell *shell, t_cmd *cmd);
int			print_cmd_not_found(const char *cmd);
int			is_directory(const char *path);
int			print_dir_error(char *cmd);
void		exec_cmd(t_shell *sh, t_cmd *cmd, char *path);
void		exec_child(t_shell *shell, t_cmd *cmd, char *path);
int			wait_child(pid_t pid);

/* -> Pipeline */
void		exec_pipe_cmd(t_shell *shell, t_cmd *cmd, int in_fd, int pipefd[2]);
int			exec_pipeline(t_shell *shell, t_cmd *cmd);

/* ENV */

t_env_var	*env_init(char **envp);
int			env_set(t_env_var *env, const char *name, const char *val);
int			env_unset(t_env_var *env, const char *name);
int			env_var_cmp_name(void *var_ptr, void *name_ref);
int			env_var_cmp_var(void *var1_ptr, void *var2_ptr);
void		env_var_free(void *var_ptr);
int			env_var_is_exportable(void *var_ptr);
char		**env_build_arr(t_env_var *env);
char		*env_build_str(t_env_var *var);
void		env_free(t_env_var *env);
char		*env_get(t_env_var *env, const char *name);
void		ft_free_array(char **array);
t_env_var	*ft_lstfind(t_env_var *lst, void *data_ref,
				int (*cmp)(void *, void *));
void		ft_lstsort(t_env_var **lst, int (*cmp)(void *, void *));
t_env_var	*ft_lstsort_dup(t_env_var *lst, int (*cmp)(void *, void *));
void		ft_lstdelone_if(t_env_var **lst, void *data_ref,
				int (*cmp)(void *, void *), void (*del)(void *));
void		ft_lstswap(t_env_var *a, t_env_var *b);
t_env_var	*ft_lstdup(t_env_var *lst);
int			ft_lstiter_ctx(t_env_var *lst, int (*f)(void *, void *), void *ctx);
int			ft_lstcount_if(t_env_var *lst, int (*f)(void *));
int			ft_strcmp(char *s1, char *s2);
void		ft_lstiter_env(t_env_var *lst, void (*f)(void *));
void		ft_lstclear_env(t_env_var *lst);
void		ft_lstadd_back_env(t_env_var **env, t_env_var *new);
t_env_var	*ft_lstnew_env(const char *name, const char *value);
void		ft_lstdelone_env(t_env_var *lst, void (*del)(void*));

/* Heredoc test*/
int			verif_heredoc(t_shell *sh, t_token *tokens);
int			setup_heredoc(t_cmd *cmd);
int			ft_cmp_heredoc(char *eof, char *returngnl);
void		print_heredoc_eof_warning(int line, char *eof_hd);
void		heredoc_cleanup(int stdin_backup, char *new_value,
				char *gnlreturn, char *eof_hd);
char		*remove_quotes(char *input);

/* signals */
extern volatile sig_atomic_t	g_signal_received;

void		setup_signals_interactive(void);
void		setup_signals_execution(void);
void		setup_signals_child(void);
void		setup_heredoc_signals(void);
void		handle_sigint_heredoc(int sig);
void		handle_sigquit_execution(int sig);
void		handle_sigint_interactive(int sig);
void		reset_signals(void);

void		print_file_error(const char *file);

#endif