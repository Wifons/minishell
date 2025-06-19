/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:44:09 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:44:10 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	bubble_pass(t_env_var *lst, int (*cmp)(void *, void *))
{
	int	swapped;

	swapped = 0;
	while (lst && lst->next)
	{
		if (cmp(lst, lst->next) > 0)
		{
			ft_lstswap(lst, lst->next);
			swapped = 1;
		}
		lst = lst->next;
	}
	return (swapped);
}

void	ft_lstsort(t_env_var **lst, int (*cmp)(void *, void *))
{
	if (!lst || !*lst || !cmp)
		return ;
	while (bubble_pass(*lst, cmp))
		;
}

t_env_var	*ft_lstsort_dup(t_env_var *lst, int (*cmp)(void *, void *))
{
	t_env_var	*copy;

	if (!lst)
		return (NULL);
	copy = ft_lstdup(lst);
	if (!copy)
		return (NULL);
	ft_lstsort(&copy, cmp);
	return (copy);
}
