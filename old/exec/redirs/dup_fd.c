#include "../../minishell.h"

/* Duplicate fd to target and close original fd */
int	dup2_close(int fd, int target)
{
	if (dup2(fd, target) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (SUCCESS);
}
