#include "../minishell.h"

t_list	*ft_lstfind(t_list *lst, void *data_ref, int (*cmp)(void *, void *))
{
	if (!cmp)
		return (NULL);
	while (lst)
	{
		if (cmp(lst->content, data_ref) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
