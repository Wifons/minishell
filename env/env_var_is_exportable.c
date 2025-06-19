/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_is_exportable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:43:47 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:43:48 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_var_is_exportable(void *var_ptr)
{
	t_env_var	*var;

	if (!var_ptr)
		return (0);
	var = (t_env_var *)var_ptr;
	if (!var->name)
		return (0);
	if (!var->value)
		return (0);
	if (ft_strcmp(var->name, "_") == 0)
		return (0);
	return (1);
}
