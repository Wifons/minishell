#include "../minishell.h"

void	ft_lstswap(t_list *a, t_list *b)
{
	void	*tmp;

	if (!a || !b)
		return ;
	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}
