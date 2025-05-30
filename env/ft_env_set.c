#include "../minishell.h"

static char *create_env_entry(char *name, char *value)
{
	char *entry;
	int total_len;
	int name_len;
	int value_len;

	if (!name)
		return (NULL);
	name_len = ft_strlen(name);
	value_len = 0;
	if (value)
		value_len = ft_strlen(value);
	total_len = name_len + value_len + 2;
	entry = malloc(total_len);
	if (!entry)
		return (NULL);
	strcpy(entry, name);
	if (value)
	{
		strcat(entry, "=");
		strcat(entry, value);
	}
	return (entry);
}

static int ft_env_update_at(char ***env, int idx, char *name, char *value)
{
	char *new_entry;

	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (-1);
	free((*env)[idx]);
	(*env)[idx] = new_entry;
	return (0);
}

static int ft_env_add_new(char ***env, char *name, char *value)
{
	char **new_env;
	char *new_entry;
	int env_len;

	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (-1);
	env_len = ft_env_len(*env);
	new_env = realloc(*env, sizeof(char *) * (env_len + 2));
	if (!new_env)
	{
		free(new_entry);
		return (-1);
	}
	new_env[env_len] = new_entry;
	new_env[env_len + 1] = NULL;
	*env = new_env;
	return (0);
}

int is_valid_env_name(char *name)
{
	int i;

	if (!name || !name[0] || ft_isdigit(name[0]))
		return (0);
	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int ft_env_set(char ***env, char *name, char *value)
{
	int idx;

	if (!env || !*env || !is_valid_env_name(name))
		return (-1);
	idx = ft_env_find(*env, name);
	if (idx != -1)
		return (ft_env_update_at(env, idx, name, value));
	return (ft_env_add_new(env, name, value));
}
