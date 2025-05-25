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
