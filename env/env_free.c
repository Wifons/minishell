/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:42:35 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:43:20 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_var_free(void *var_ptr)
{
	t_env_var	*var;

	var = (t_env_var *)var_ptr;
	if (!var)
		return ;
	free(var->name);
	free(var->value);
	free(var);
}

void	env_free(t_env_var *env)
{
	if (!env)
		return ;
	ft_lstclear_env(env);
	free(env);
}
