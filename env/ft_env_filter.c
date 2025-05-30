#include "../minishell.h"

static int count_with_values(char **env)
{
	int count = 0;
	int i = 0;

	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			count++;
		i++;
	}
	return (count);
}

static int copy_valued_entries(char **src, char **dst)
{
	int i = 0;
	int j = 0;

	while (src[i])
	{
		if (ft_strchr(src[i], '='))
		{
			dst[j] = ft_strdup(src[i]);
			if (!dst[j])
				return (-1);
			j++;
		}
		i++;
	}
	dst[j] = NULL;
	return (0);
}

char **env_filter(char **env)
{
	char **filtered;
	int count;

	if (!env)
		return (NULL);
	count = count_with_values(env);
	filtered = malloc(sizeof(char *) * (count + 1));
	if (!filtered)
		return (NULL);
	if (copy_valued_entries(env, filtered) == -1)
	{
		ft_free_array(filtered);
		return (NULL);
	}
	return (filtered);
}
