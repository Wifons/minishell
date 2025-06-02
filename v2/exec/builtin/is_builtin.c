/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:23 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/29 19:35:14 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Checks if command is a minishell builtin (echo, cd, pwd, etc)*/
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
  return (ft_strcmp(cmd, "echo") == 0
        || ft_strcmp(cmd, "cd") == 0
        || ft_strcmp(cmd, "pwd") == 0
        || ft_strcmp(cmd, "export") == 0
        || ft_strcmp(cmd, "unset") == 0
        || ft_strcmp(cmd, "env") == 0
        || ft_strcmp(cmd, "exit") == 0);
}
