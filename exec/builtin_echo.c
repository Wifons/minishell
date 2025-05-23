#include "../minishell.h"

static bool is_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	builtin_echo(t_cmd *cmd)
{
	int		i;
	bool	newline;

	if (!cmd || !cmd->arguments)
		return (1);
	i = 1;
	newline = true;
	while (cmd->arguments[i] && is_n_flag(cmd->arguments[i]))
	{
		newline = false;
		i++;
	}
	while (cmd->arguments[i])
	{
		printf("%s", cmd->arguments[i]);
		if (cmd->arguments[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

