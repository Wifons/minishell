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
