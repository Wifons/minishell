/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:43:55 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:44:35 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdelone_if(t_env_var **lst, void *data_ref
	, int (*cmp)(void *, void *), void (*del)(void *))
{
	t_env_var	*cur;
	t_env_var	*prev;

	if (!lst || !*lst || !cmp)
		return ;
	cur = *lst;
	prev = NULL;
	while (cur)
	{
		if (cmp(cur->name, data_ref) == 0)
		{
			if (!prev)
				*lst = cur->next;
			else
				prev->next = cur->next;
			ft_lstdelone_env(cur, del);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
