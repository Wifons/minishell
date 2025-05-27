#include "../../minishell.h"

/* Redirect stdin to read from pipe */
void	setup_pipe_in(int *in_fd, int pipefd[2])
{
	if (*in_fd != STDIN_FILENO)
	{
		dup2_close(*in_fd, STDIN_FILENO);
		*in_fd = STDIN_FILENO;
	}
	if (pipefd[PIPE_READ] != -1)
		close(pipefd[PIPE_READ]);
	if (pipefd[PIPE_WRITE] != -1)
		close(pipefd[PIPE_WRITE]);
}

/* Redirect stdout to write to pipe */
void	setup_pipe_out(int pipefd[2])
{
	dup2_close(pipefd[PIPE_WRITE], STDOUT_FILENO);
	close(pipefd[PIPE_READ]);
}
