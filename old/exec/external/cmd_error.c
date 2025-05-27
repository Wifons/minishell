#include "../../minishell.h"

void	print_cmd_not_found(const char *cmd)
{
	ft_putstr_fd("Minishell : ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}
