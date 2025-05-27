/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:59 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:08:00 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
