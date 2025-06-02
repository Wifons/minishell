#include "../minishell.h"

void	ft_lstdelone_if(t_list **lst, void *data_ref, int (*cmp)(void *, void *), void (*del)(void *))
{
	t_list	*cur;
	t_list	*prev;

	if (!lst || !*lst || !cmp)
		return ;
	cur = *lst;
	prev = NULL;
	while (cur)
	{
		if (cmp(cur->content, data_ref) == 0)
		{
			if (!prev)
				*lst = cur->next;
			else
				prev->next = cur->next;
			ft_lstdelone(cur, del);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
