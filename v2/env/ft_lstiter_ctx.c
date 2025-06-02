#include "../minishell.h"

int	ft_lstiter_ctx(t_list *lst, int (*f)(void *, void *), void *ctx)
{
	t_list	*cur;
	int			res;

	cur = lst;
	while (cur)
	{
		res = f(cur->content, ctx);
		if (res != 0)
			return (res);
		cur = cur->next;
	}
	return (0);
}
