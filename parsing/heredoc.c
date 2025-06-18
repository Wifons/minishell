/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:57:51 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/17 19:10:37 by tcassu           ###   ########.fr       */
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

static void	print_heredoc_eof_warning(int line, char *eof_hd)
{
	write(1, "\n", 1);
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(eof_hd, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

static void	heredoc_cleanup(int stdin_backup, char *new_value, char *gnlreturn, char *eof_hd)
{
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	free(new_value);
	free(gnlreturn);
	free(eof_hd);
	setup_signals_interactive();
}

char	*ft_heredoc(t_shell *sh, char *eof_hd)
{
	char	*new_value = ft_strdup("");
	char	*gnlreturn = NULL;
	char	*tmp;
	int		stdin_backup = dup(STDIN_FILENO);
	int		heredoc_start_line = sh->curr_line;

	setup_heredoc_signals();
	while (1)
	{
		write(1, "> ", 2);
		gnlreturn = get_next_line(0);
		if (g_signal_received == SIGINT)
		{
			heredoc_cleanup(stdin_backup, new_value, gnlreturn, eof_hd);
			return (NULL);
		}
		if (!gnlreturn)
		{
			print_heredoc_eof_warning(heredoc_start_line, eof_hd);
			break ;
		}
		if (ft_cmp_heredoc(eof_hd, gnlreturn))
		{
			free(gnlreturn);
			break ;
		}
		tmp = new_value;
		new_value = ft_strjoin(new_value, gnlreturn);
		free(gnlreturn);
		if (new_value)
			free(tmp);
		sh->curr_line++;
	}
	heredoc_cleanup(stdin_backup, NULL, NULL, eof_hd);
	return (new_value);
}

int	verif_heredoc(t_shell *sh, t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp && (tmp->type == HEREDOC))
		{
			if (!tmp->next)
			{
				printf("Minishell : Syntax error near unexpected token 'newline'\n");
				return (1);
			}
			if (tmp->next->type != WORD)
			{
				printf("Minishell : syntax error3\n");
				return (1);
			}
			tmp = tmp->next;
			tmp->value = remove_quotes(tmp->value);
			tmp->value = ft_heredoc(sh, tmp->value);
			if (!tmp->value)
				return (130);
		}
		tmp = tmp->next;
	}
	return (0);
}
