#include "../minishell.h"

t_env_var	*ft_lstfind(t_env_var *lst, void *data_ref, int (*cmp)(void *, void *))
{
	if (!cmp)
		return (NULL);
	while (lst)
	{
		if (cmp(lst->name, data_ref) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
