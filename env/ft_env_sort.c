#include "../minishell.h"

static int	env_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == '=' && s2[i] != '=')
		return (-1);
	if (s1[i] != '=' && s2[i] == '=')
		return (1);
	return (s1[i] - s2[i]);
}

static void	ft_env_sort(char **env)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	len = ft_env_len(env);
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (env_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**ft_env_dup_sort(char **env)
{
	char	**sorted_copy;

	sorted_copy = ft_env_dup(env);
	if (!sorted_copy)
		return (NULL);
	ft_env_sort(sorted_copy);
	return (sorted_copy);
}
