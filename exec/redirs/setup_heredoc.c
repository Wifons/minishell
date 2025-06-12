#include "../../minishell.h"

static int create_heredoc_pipe(char *heredoc_content)
{
	int pipefd[2];
	pid_t pid;
	int status;
	
	// On crée le pipe
	if (create_pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close_pipe(pipefd);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipefd[PIPE_READ]);
		if (heredoc_content)
			ft_putstr_fd(heredoc_content, pipefd[PIPE_WRITE]);
		close(pipefd[PIPE_WRITE]);
		exit(SUCCESS);
	}
	close(pipefd[PIPE_WRITE]);
	waitpid(pid, &status, 0);
	return (pipefd[PIPE_READ]);
}

int setup_heredoc(t_cmd *cmd)
{
	int heredoc_fd;

	if (!cmd->heredoc_buff)
		return (SUCCESS);
	heredoc_fd = create_heredoc_pipe(cmd->heredoc_buff);
	if (heredoc_fd == -1)
		return (GENERAL_ERROR);
	return (dup2_close(heredoc_fd, STDIN_FILENO));
}
