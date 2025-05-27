/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:51 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:07:52 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Create a pipe and check for error */
int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (SUCCESS);
}

/* Close both ends of a pipe */
void	close_pipe(int pipefd[2])
{
	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
}

/* Count number of pipes in command chain */
int	count_pipes(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		if (cmd->next_pipe)
			count++;
		cmd = cmd->next;
	}
	return (count);
}
