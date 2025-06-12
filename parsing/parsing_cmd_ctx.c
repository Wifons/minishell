/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_ctx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:56:11 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/12 13:26:59 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_parse_struct(t_parse_cmd *parse, t_token *tokens, t_shell *shell)
{
	t_cmd *cmd;
	
	cmd = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	init_cmd(cmd);
	parse->cmd = malloc(sizeof(t_cmd *));
	parse->head_cmd = malloc(sizeof(t_cmd *));
	parse->tmp = malloc(sizeof(t_token *));
	if (!parse->cmd || !parse->head_cmd || !parse->tmp)
	{
		free(cmd);
		free(parse->cmd);
		free(parse->head_cmd);
		free(parse->tmp);
		return (0);
	}
	*(parse->cmd) = cmd;
	*(parse->head_cmd) = cmd;
	*(parse->tmp) = tokens;
	parse->tokens = tokens;
	parse->shell = shell;
	return (1);
}
