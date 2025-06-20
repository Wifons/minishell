/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:41:56 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/20 15:10:53 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmp_heredoc(char *eof, char *returngnl)
{
	size_t	len;

	if (!returngnl)
		return (0);
	len = ft_strlen(returngnl);
	if (len > 0 && returngnl[len - 1] == '\n')
		returngnl[len - 1] = '\0';
	if (ft_strcmp(eof, returngnl) == 0)
		return (1);
	if (len > 0)
		returngnl[len - 1] = '\n';
	return (0);
}

void	print_heredoc_eof_warning(int line, char *eof_hd)
{
	write(1, "\n", 1);
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(eof_hd, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

void	heredoc_cleanup(int stdin_backup, char *new_value
	, char *gnlreturn, char *eof_hd)
{
	if (stdin_backup >= 0)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	free(new_value);
	free(gnlreturn);
	free(eof_hd);
	// setup_signals_interactive();
}

void	add_heredoc(t_cmd *cmd, t_token **tokens)
{
	*tokens = (*tokens)->next;
	if (cmd->heredoc_buff)
		free(cmd->heredoc_buff);
	if ((*tokens)->value)
		cmd->heredoc_buff = ft_strdup((*tokens)->value);
	else
		cmd->heredoc_buff = ft_strdup("");
}
