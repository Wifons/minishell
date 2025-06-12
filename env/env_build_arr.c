#include "../minishell.h"

static int	add_var(void *data, void *ctx)
{
	t_env_var	*var;
	char			**arr;
	char			*str;
	int				*i;

	var = (t_env_var *)data;
	arr = ((void **)ctx)[0];
	i = ((void **)ctx)[1];
	if (!env_var_is_exportable(var))
		return (0);
	str = env_build_str(var);
	if (!str)
		return (-1);
	arr[*i] = str;
	(*i)++;
	return (0);
}

char	**env_build_arr(t_env_var *env)
{
	char	**arr;
	int		count;
	int		i;
	void	*ctx[2];

	if (!env)
		return (NULL);
	count = ft_lstcount_if(env, env_var_is_exportable);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	ctx[0] = arr;
	ctx[1] = &i;
	if (ft_lstiter_ctx(env, add_var, ctx) != 0)
	{
		ft_free_array(arr);
		return (NULL);
	}
	arr[i] = NULL;
	return (arr);
}
