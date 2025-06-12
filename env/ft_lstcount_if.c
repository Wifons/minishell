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
