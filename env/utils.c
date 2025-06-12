#include "../minishell.h"

void	ft_lstiter_env(t_env_var *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}

void	ft_lstclear_env(t_env_var *lst)
{
	t_env_var *tmp;

	if (!lst)
		return ;
	if (lst)
	{
		while (lst)
		{
			tmp = lst;
			lst = lst->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
		}
	}
	lst = NULL;
}


void	ft_lstadd_back_env(t_env_var **env, t_env_var *new)
{
	t_env_var	*last;

	if (!new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
    last = *env;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

t_env_var	*ft_lstnew_env(const char *name, const char *value)
{
	t_env_var	*list;

	list = malloc(sizeof(t_env_var));
	if (!list)
		return (NULL);
	list->name = ft_strdup(name);
	list->value = ft_strdup(value);
	list->next = NULL;
	return (list);
}


void	ft_lstdelone_env(t_env_var *lst, void (*del)(void*))
{
	if (lst)
	{
		del(lst);
	}
}