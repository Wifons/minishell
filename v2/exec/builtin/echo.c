/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:15 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:07:16 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	is_n_flag(const char *arg)
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

static void	print_args(char **args, int i)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

int	builtin_echo(t_cmd *cmd)
{
	int		i;
	bool	newline;

	if (!cmd || !cmd->arguments)
		return (GENERAL_ERROR);
	i = 1;
	newline = true;
	while (cmd->arguments[i] && is_n_flag(cmd->arguments[i]))
	{
		newline = false;
		i++;
	}
	print_args(cmd->arguments, i);
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}
