#include "../../minishell.h"

static int legal_number(char *string, long *result)
{
	char *end;
	long val;

	if (!string || !*string)
		return (0);
	errno = 0;
	val = strtol(string, &end, 10);
	if (errno != 0 || *end != '\0' || end == string)
		return (0);
	*result = val;
	return (1);
}

static void sh_neednumarg(char *s)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(s ? s : "''", STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

static void no_args(char **args, int index)
{
	if (args[index])
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
}

static int is_option(char *arg)
{
	long dummy;

	if (!arg || arg[0] != '-')
		return (0);
	if (arg[1] == '\0')
		return (0);
	if (arg[1] == '-' && arg[2] == '\0')
		return (1);
	if (legal_number(arg, &dummy))
		return (0);
	return (1);
}

static int get_exitstat(char **args, t_shell *sh, int *too_many_args)
{
	int status;
	long sval;
	char *arg;
	int i;

	*too_many_args = 0;
	i = 1;
	if (args[i] && is_option(args[i]))
		i++;
	if (!args[i])
		return (sh->global_status);
	arg = args[i];
	if (!arg || !legal_number(arg, &sval))
	{
		sh_neednumarg(arg);
		return (2);
	}
	if (args[i + 1])
	{
		no_args(args, i + 1);
		*too_many_args = 1;
		return (1);
	}
	status = sval & 255;
	return (status);
}

int builtin_exit(t_shell *sh, t_cmd *cmd)
{
	int exit_value;
	int too_many_args;

	ft_putendl_fd("exit", STDERR_FILENO);
	exit_value = get_exitstat(cmd->arguments, sh, &too_many_args);
	if (too_many_args)
		return (1);
	sh->should_exit = 1;
	return (exit_value);
}
