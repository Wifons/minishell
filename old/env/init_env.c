#include "../minishell.h"

static int	copy_env_vars(char **src, char **dst, int count)
{
    int	i;

    i = 0;
    while (i < count)
    {
        dst[i] = ft_strdup(src[i]);
        if (!dst[i])
            return (GENERAL_ERROR);
        i++;
    }
    dst[i] = NULL;
    return (SUCCESS);
}

static int	alloc_env(t_shell *shell, int count)
{
    shell->env = malloc(sizeof(char *) * (count + 1));
    if (!shell->env)
        return (GENERAL_ERROR);
    return (SUCCESS);
}

static void	set_shlvl(t_shell *shell)
{
    char	*shlvl_str;
    char	*new_shlvl;
    int		shlvl;

    shlvl_str = get_env_value(shell, "SHLVL");
    if (!shlvl_str)
        shlvl = 0;
    else
        shlvl = ft_atoi(shlvl_str);
    shlvl++;
    new_shlvl = ft_itoa(shlvl);
    if (new_shlvl)
    {
        set_env_value(shell, "SHLVL", new_shlvl);
        free(new_shlvl);
    }
}

int	init_env(t_shell *shell, char **envp)
{
    int	count;

    count = count_env_vars(envp);
    if (alloc_env(shell, count) == GENERAL_ERROR)
        return (GENERAL_ERROR);
    if (copy_env_vars(envp, shell->env, count) == GENERAL_ERROR)
    {
        free(shell->env);
        shell->env = NULL;
        return (GENERAL_ERROR);
    }
    set_shlvl(shell);
    return (SUCCESS);
}