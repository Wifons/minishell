/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:34:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 21:37:37 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_option(char *arg)
{
	long	dummy;

	if (!arg || arg[0] != '-')
		return (0);
	if (arg[1] == '\0')
		return (0);
	if (arg[1] == '-' && arg[2] == '\0')
		return (1);
	if (legal_number(arg, &dummy))
		return (0);
	return (1);
}
