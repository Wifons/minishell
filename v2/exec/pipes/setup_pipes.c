/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:55 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:07:56 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Redirect stdin to read from pipe */
void	setup_pipe_in(int pipefd[2])
{
	dup2(pipefd[PIPE_READ], STDIN_FILENO);
	close_pipe(pipefd);
}

/* Redirect stdout to write to pipe */
void	setup_pipe_out(int pipefd[2])
{
	dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
	close_pipe(pipefd);
}
