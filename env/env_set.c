#include "../minishell.h"

static	t_env_var	*create_env_var(const char *name, const char *value)
{
	t_env_var	*var;

	if (!name)
		return (NULL);
	var = ft_calloc(1, sizeof(t_env_var));
	if (!var)
		return (NULL);
	var->name = ft_strdup(name);
	if (!var->name)
	{
		free(var);
		return (NULL);
	}
	if (value)
	{
		var->value = ft_strdup(value);
		if (!var->value)
		{
			free(var->name);
			free(var);
			return (NULL);
		}
	}
	return (var);
}

static int	update_existing_var(t_env_var *var, const char *value)
{
	char	*new_val;

	if (!var)
		return (-1);
	free(var->value);
	var->value = NULL;
	if (!value)
		return (0);
	new_val = ft_strdup(value);
	if (!new_val)
		return (-1);
	var->value = new_val;
	return (0);
}

int	env_set(t_list *env, const char *name, const char *val)
{
	t_list		*existing;
	t_env_var	*new_var;
	t_list		*new_node;

	if (!env || !name)
		return (-1);
	existing = ft_lstfind(env, (void *)name, env_var_cmp_name);
	if (existing)
		return (update_existing_var((t_env_var *)existing->content, val));
	new_var = create_env_var(name, val);
	if (!new_var)
		return (-1);
	new_node = ft_lstnew(new_var);
	if (!new_node)
	{
		env_var_free(new_var);
		return (-1);
	}
	ft_lstadd_back(&env, new_node);
	return (0);
}
