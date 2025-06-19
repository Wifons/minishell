/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:44:13 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:44:50 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstswap(t_env_var *a, t_env_var *b)
{
	char	*tmp_name;
	char	*tmp_value;

	if (!a || !b)
		return ;
	tmp_name = a->name;
	tmp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = tmp_name;
	b->value = tmp_value;
}
