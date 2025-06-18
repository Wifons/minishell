/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:08:06 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 16:11:32 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// /* Setup input redirection (< file) */
// static int	setup_input_redir(const char *file)
// {
// 	int	fd;

// 	fd = open_infile(file);
// 	if (fd == -1)
// 		return (-1);
// 	return (dup2_close(fd, STDIN_FILENO));
// }

// /* Setup output redirection (> file) */
// static int	setup_output_redir(const char *file)
// {
// 	int	fd;

// 	fd = open_outfile(file, false);
// 	if (fd == -1)
// 		return (-1);
// 	return (dup2_close(fd, STDOUT_FILENO));
// }

// /* Setup append redirection (>> file) */
// static int	setup_append_redir(const char *file)
// {
// 	int	fd;

// 	fd = open_outfile(file, true);
// 	if (fd == -1)
// 		return (-1);
// 	return (dup2_close(fd, STDOUT_FILENO));
// }

/* Setup all redirections for a command */
int setup_redirs(t_cmd *cmd)
{
	t_redir_ordered	*redir;
	int	fd;

	if (!cmd)
		return (SUCCESS);
	if (cmd->heredoc_buff)
		if (setup_heredoc(cmd) == -1)
			return (-1);
	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->redirect == 1)
		{
			fd = open_infile(redir->filename);
			if (fd == -1)
				return (-1);
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else
		{
			fd = open_outfile(redir->filename, redir->append);
			if (fd == -1)
				return (-1);
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		redir = redir->next;
	}
	return (SUCCESS);
}
