/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:24:42 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 20:39:12 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_redir_ordered(t_cmd *cmd, int redirect, int append
	, const char *filename)
{
	t_redir_ordered	*new;
	t_redir_ordered	*tmp;

	new = malloc(sizeof(t_redir_ordered));
	if (!new)
		return ;
	new->redirect = redirect;
	new->append = append;
	new->filename = ft_strdup(filename);
	new->next = NULL;
	if (!cmd->redir_list)
		cmd->redir_list = new;
	else
	{
		tmp = cmd->redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_arg(t_cmd *cmd, char *value)
{
	int		i;
	int		j;
	char	**args;

	i = 0;
	if (cmd->arguments)
		while (cmd->arguments[i])
			i++;
	args = malloc(sizeof(char *) * (i + 2));
	if (!args)
		return ;
	j = 0;
	while (j < i)
	{
		args[j] = cmd->arguments[j];
		j++;
	}
	args[j] = ft_strdup(value);
	args[j + 1] = NULL;
	free(cmd->arguments);
	cmd->arguments = args;
}

void	add_l_red(t_cmd *cmd, t_token **tokens)
{
	char	*file;

	*tokens = (*tokens)->next;
	file = ft_strdup((*tokens)->value);
	if (!file)
		return ;
	add_redir_ordered(cmd, 1, 0, (*tokens)->value);
	if (cmd->l_redirect)
		free(cmd->l_redirect);
	cmd->l_redirect = file;
}

void	add_r_red(t_cmd *cmd, t_token **tokens)
{
	char	*file;

	*tokens = (*tokens)->next;
	file = ft_strdup((*tokens)->value);
	if (!file)
		return ;
	add_redir_ordered(cmd, 0, 0, (*tokens)->value);
	if (cmd->r_redirect)
		free(cmd->r_redirect);
	cmd->r_redirect = file;
}

void	add_app_red(t_cmd *cmd, t_token **tokens)
{
	*tokens = (*tokens)->next;
	add_redir_ordered(cmd, 0, 1, (*tokens)->value);
	if (cmd->app_redirect)
		free(cmd->app_redirect);
	cmd->app_redirect = ft_strdup((*tokens)->value);
}
