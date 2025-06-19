/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount_if.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:43:51 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:43:52 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstcount_if(t_env_var *lst, int (*f)(void *))
{
	int			count;
	t_env_var	*curr;

	count = 0;
	curr = lst;
	while (curr)
	{
		if (f(curr))
			count++;
		curr = curr->next;
	}
	return (count);
}
