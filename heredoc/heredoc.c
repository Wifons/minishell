/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:57:51 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 15:59:04 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_join(t_shell *shell, char **new_value, char *line, char *eof)
{
	char	*tmp;
	char	*eof_clean;

	tmp = *new_value;
	eof_clean = remove_quotes(eof);
	if (ft_strcmp(eof, eof_clean) == 0)
	{
		line = expand_var(shell, line);
		line = expand_cmd_code(shell, line);
	}
	free(eof_clean);
	*new_value = ft_strjoin(*new_value, line);
	free(line);
	if (*new_value)
		free(tmp);
	shell->curr_line++;
	return (0);
}

int	heredoc_process(t_shell *shell, char **new_value, char *line, char *eof)
{
	int		result;
	char	*tmp_eof;
	char	*clean_eof;

	tmp_eof = ft_strdup(eof);
	clean_eof = remove_quotes(eof);
	if (ft_cmp_heredoc(clean_eof, line))
	{
		free(line);
		free(tmp_eof);
		free(clean_eof);
		return (1);
	}
	result = heredoc_join(shell, new_value, line, tmp_eof);
	free(clean_eof);
	free(tmp_eof);
	return (result);
}

int	heredoc_loop(t_shell *shell, char **new_value, char	*eof, int start)
{
	char	*gnlreturn;

	while (1)
	{
		write(1, "> ", 2);
		gnlreturn = get_next_line(0);
		if (g_signal_received == SIGINT)
		{
			heredoc_cleanup(-1, *new_value, gnlreturn, eof);
			return (1);
		}
		if (!gnlreturn)
		{
			print_heredoc_eof_warning(start, eof);
			break ;
		}
		if (heredoc_process(shell, new_value, gnlreturn, eof))
			break ;
	}
	return (0);
}

char	*ft_heredoc(t_shell *shell, char *eof)
{
	char	*new_value;
	int		stdin_backup;
	int		interupt;

	stdin_backup = dup(STDIN_FILENO);
	setup_heredoc_signals();
	new_value = ft_strdup("");
	interupt = heredoc_loop(shell, &new_value, eof, shell->curr_line);
	if (interupt)
		return (NULL);
	heredoc_cleanup(stdin_backup, NULL, NULL, eof);
	return (new_value);
}

int	verif_heredoc(t_shell *sh, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp && (tmp->type == HEREDOC))
		{
			tmp = tmp->next;
			tmp->value = ft_heredoc(sh, tmp->value);
			if (!tmp->value)
				return (130);
		}
		tmp = tmp->next;
	}
	return (0);
}
