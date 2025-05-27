#include "../minishell.h"

/* Execute builtin with redirections setup */
static int	exec_builtin_with_redir(t_shell *shell, t_cmd *cmd)
{
	if (setup_redirs(cmd) == -1)
		return (GENERAL_ERROR);
	return (exec_builtin(shell, cmd));
}

/* Execute a single command (no pipes) - builtin or external */
int	exec_single(t_shell *shell, t_cmd *cmd)
{
	if (is_builtin(cmd->arguments[0]))
		return (exec_builtin_with_redir(shell, cmd));
	return (exec_external(shell, cmd));
}
