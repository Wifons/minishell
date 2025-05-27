#include "../../minishell.h"

static int create_heredoc_pipe(char *delimiter)
{
	int pipefd[2];
	char *line;
	pid_t pid;

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
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break;
			}
			ft_putstr_fd(line, pipefd[PIPE_WRITE]);
			ft_putchar_fd('\n', pipefd[PIPE_WRITE]);
			free(line);
		}
		close(pipefd[PIPE_WRITE]);
		exit(SUCCESS);
	}
	close(pipefd[PIPE_WRITE]);
	wait(NULL);
	return (pipefd[PIPE_READ]);
}

int setup_heredoc(t_cmd *cmd)
{
	int heredoc_fd;

	if (!cmd->heredoc_delimiter)
		return (SUCCESS);
	heredoc_fd = create_heredoc_pipe(cmd->heredoc_delimiter);
	if (heredoc_fd == -1)
		return (GENERAL_ERROR);
	return (dup2_close(heredoc_fd, STDIN_FILENO));
}
