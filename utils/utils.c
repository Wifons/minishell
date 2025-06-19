/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:32:45 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 17:49:18 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clean(t_token *tokens)
{
	t_token	*tmp;

	if (tokens)
	{
		while (tokens)
		{
			tmp = tokens;
			tokens = tokens->next;
			free(tmp->value);
			free(tmp);
		}
	}
}
