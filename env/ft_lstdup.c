/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:43:59 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:44:00 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_var	*ft_lstdup(t_env_var *lst)
{
	t_env_var	*new_lst;
	t_env_var	*new_node;
	t_env_var	*cur;

	if (!lst)
		return (NULL);
	new_lst = NULL;
	cur = lst;
	while (cur)
	{
		new_node = ft_lstnew_env(cur->name, cur->value);
		if (!new_node)
		{
			ft_lstclear_env(new_lst);
			return (NULL);
		}
		ft_lstadd_back_env(&new_lst, new_node);
		cur = cur->next;
	}
	return (new_lst);
}
