#include "../minishell.h"

static int	bubble_pass(t_list *lst, int (*cmp)(void *, void *))
{
	int	swapped;

	swapped = 0;
	while (lst && lst->next)
	{
		if (cmp(lst->content, lst->next->content) > 0)
		{
			ft_lstswap(lst, lst->next);
			swapped = 1;
		}
		lst = lst->next;
	}
	return (swapped);
}

void	ft_lstsort(t_list **lst, int (*cmp)(void *, void *))
{
	if (!lst || !*lst || !cmp)
		return ;
	while (bubble_pass(*lst, cmp))
		;
}

t_list	*ft_lstsort_dup(t_list *lst, int (*cmp)(void *, void *))
{
	t_list	*copy;

	if (!lst)
		return (NULL);
	copy = ft_lstdup(lst);
	if (!copy)
		return (NULL);
	ft_lstsort(&copy, cmp);
	return (copy);
}
