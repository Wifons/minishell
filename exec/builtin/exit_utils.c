/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:34:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/20 01:17:47 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

const char	*normalize_number(const char *str, int *sign)
{
	while (isspace(*str))
		str++;
	*sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	return (str);
}

int	compare_number_str(const char *a, const char *b)
{
	size_t	len_a;
	size_t	len_b;
	int		cmp;

	len_a = strlen(a);
	len_b = strlen(b);
	if (len_a > len_b)
		return (1);
	if (len_a < len_b)
		return (-1);
	cmp = strcmp(a, b);
	return (cmp);
}

int	compare_to_long_limits(const char *str)
{
	const char	*max_str;
	const char	*min_str;
	int			sign;
	const char	*num;
	int			cmp;

	max_str = "9223372036854775807";
	min_str = "9223372036854775808";
	num = normalize_number(str, &sign);
	if (sign == 1)
		cmp = compare_number_str(num, max_str);
	else
		cmp = compare_number_str(num, min_str);
	if (cmp > 0)
	{
		if (sign == 1)
			return (1);
		else
			return (-1);
	}
	return (0);
}

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

long	ft_atol(const char *str)
{
	int		i;
	long	sign;
	long	result;
	int		t;

	i = 0;
	t = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
		t++;
	}
	if (t > 1)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	return (result * sign);
}
