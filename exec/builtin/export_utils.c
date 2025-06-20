/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:03:15 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/19 22:16:16 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_declared_var(void *data)
{
	t_env_var	*var;

	if (!data)
		return ;
	var = (t_env_var *)data;
	if (!var->name || ft_strcmp(var->name, "_") == 0)
		return ;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(var->name, STDOUT_FILENO);
	if (var->value != NULL)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(var->value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	print_all_vars(t_env_var *env)
{
	t_env_var	*sorted;

	if (!env)
		return (-1);
	sorted = ft_lstsort_dup(env, env_var_cmp_var);
	if (!sorted)
		return (-1);
	ft_lstiter_env(sorted, print_declared_var);
	ft_lstclear_env(sorted);
	return (0);
}
