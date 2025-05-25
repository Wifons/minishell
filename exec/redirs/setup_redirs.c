#include "../../minishell.h"

/* Setup input redirection (< file) */
static int	setup_input_redir(const char *file)
{
	int	fd;

	fd = open_infile(file);
	if (fd == -1)
		return (-1);
	return (dup2_close(fd, STDIN_FILENO));
}

/* Setup output redirection (> file) */
static int	setup_output_redir(const char *file)
{
	int	fd;

	fd = open_outfile(file, false);
	if (fd == -1)
		return (-1);
	return (dup2_close(fd, STDOUT_FILENO));
}

/* Setup append redirection (>> file) */
static int	setup_append_redir(const char *file)
{
	int	fd;

	fd = open_outfile(file, true);
	if (fd == -1)
		return (-1);
	return (dup2_close(fd, STDOUT_FILENO));
}

/* Setup all redirections for a command */
int setup_redirs(t_cmd *cmd)
{
	if (cmd->l_redirect)
		if (setup_input_redir(cmd->l_redirect) == -1)
			return (-1);
	if (cmd->r_redirect)
		if (setup_output_redir(cmd->r_redirect) == -1)
			return (-1);
	if (cmd->app_redirect)
		if (setup_append_redir(cmd->app_redirect) == -1)
			return (-1);
	return (SUCCESS);
}
