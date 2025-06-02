#include "../minishell.h"

t_list	*ft_lstdup(t_list *lst)
{
	t_list	*new_lst;
	t_list	*new_node;
	t_list	*cur;

	if (!lst)
		return (NULL);
	new_lst = NULL;
	cur = lst;
	while (cur)
	{
		new_node = ft_lstnew(cur->content);
		if (!new_node)
		{
			ft_lstclear(&new_lst, NULL);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		cur = cur->next;
	}
	return (new_lst);
}
