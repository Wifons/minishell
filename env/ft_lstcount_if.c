#include "../minishell.h"

int	ft_lstcount_if(t_list *lst, int (*f)(void *))
{
	int			count;
	t_list	*curr;

	count = 0;
	curr = lst;
	while (curr)
	{
		if (f(curr->content))
			count++;
		curr = curr->next;
	}
	return (count);
}
