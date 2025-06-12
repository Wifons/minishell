#include "../minishell.h"

void	ft_lstdelone_if(t_env_var **lst, void *data_ref, int (*cmp)(void *, void *), void (*del)(void *))
{
	t_env_var	*cur;
	t_env_var	*prev;

	if (!lst || !*lst || !cmp)
		return ;
	cur = *lst;
	prev = NULL;
	while (cur)
	{
		if (cmp(cur->name, data_ref) == 0)
		{
			if (!prev)
				*lst = cur->next;
			else
				prev->next = cur->next;
			ft_lstdelone_env(cur, del);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
