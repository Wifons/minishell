/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:20:05 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 02:52:45 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_pwd(t_shell *shell, char **arguments)
{
	char	*cwd;
	int		i;

	i = 0;
	while (arguments[++i])
	{
		if (arguments[i][0] == '-' && !(arguments[i][1] == '\0'
			|| (arguments[i][1] == '-' && arguments[i][2] == '\0')))
		{
			ft_putstr_fd("minishell: pwd: -", STDERR_FILENO);
			ft_putchar_fd(arguments[i][1], STDERR_FILENO);
			ft_putendl_fd(": invalid option", STDOUT_FILENO);
			shell->global_status = 2;
			return (2);
		}
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (GENERAL_ERROR);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (SUCCESS);
}
