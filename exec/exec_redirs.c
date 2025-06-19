/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:47:11 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 21:48:56 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_in(t_redir_ordered *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		print_file_error(redir->filename);
		return (1);
	}
	close(fd);
	return (0);
}

int	redirect_out(t_redir_ordered *redir)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (redir->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(redir->filename, flags, 0644);
	if (fd < 0)
	{
		print_file_error(redir->filename);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_all_redirs(t_redir_ordered *redir)
{
	while (redir)
	{
		if (redir->redirect == 1)
		{
			if (redirect_in(redir) != 0)
				return (1);
		}
		else
		{
			if (redirect_out(redir) != 0)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}
