#include "../minishell.h"

int	ft_lstiter_ctx(t_env_var *lst, int (*f)(void *, void *), void *ctx)
{
	t_env_var	*cur;
	int			res;

	cur = lst;
	while (cur)
	{
		res = f(cur, ctx);
		if (res != 0)
			return (res);
		cur = cur->next;
	}
	return (0);
}
