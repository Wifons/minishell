/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:28 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/11 21:48:38 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_cmd_not_found(const char *cmd)
{
	ft_putstr_fd("minishell : ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (CMD_NOT_FOUND);
}
