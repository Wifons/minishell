/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_cmp_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:43:42 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:43:43 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_var_cmp_name(void *var_ptr, void *name_ref)
{
	char	*var;
	char	*name;

	var = (char *)var_ptr;
	name = (char *)name_ref;
	if (!var || !name)
		return (-1);
	return (ft_strcmp(var, name));
}

int	env_var_cmp_var(void *var1_ptr, void *var2_ptr)
{
	t_env_var	*var1;
	t_env_var	*var2;

	var1 = (t_env_var *)var1_ptr;
	var2 = (t_env_var *)var2_ptr;
	if (!var1 || !var1->name || !var2 || !var2->name)
		return (0);
	return (ft_strcmp(var1->name, var2->name));
}
