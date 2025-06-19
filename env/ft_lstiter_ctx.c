/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_ctx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:44:06 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:44:07 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstiter_ctx(t_env_var *lst, int (*f)(void *, void *), void *ctx)
{
	t_env_var	*cur;
	int			res;

	cur = lst;
	while (cur)
	{
		res = f(cur, ctx);
		if (res != 0)
			return (res);
		cur = cur->next;
	}
	return (0);
}
