/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:44:02 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:44:43 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_var	*ft_lstfind(t_env_var *lst, void *data_ref
	, int (*cmp)(void *, void *))
{
	if (!cmp)
		return (NULL);
	while (lst)
	{
		if (cmp(lst->name, data_ref) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
