#include "../minishell.h"

static char *get_cwd_safe(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("/"));
	return (cwd);
}

static char *calc_next_shlvl(char **env)
{
	char *curr;
	int lvl;

	curr = ft_env_get(env, "SHLVL");
	lvl = 1;
	if (curr)
		lvl = ft_atoi(curr) + 1;
	return (ft_itoa(lvl));
}

static int set_shell_vars(char ***env)
{
	char *cwd;
	char *shlvl;
	int status = 0;

	cwd = get_cwd_safe();
	shlvl = calc_next_shlvl(*env);
	if (!cwd || !shlvl)
		status = -1;
	if (status == 0 && ft_env_set(env, "PWD", cwd) == -1)
		status = -1;
	if (status == 0 && ft_env_set(env, "SHLVL", shlvl) == -1)
		status = -1;
	free(cwd);
	free(shlvl);
	return (status);
}

static int init_oldpwd(char ***env)
{
	if (!ft_env_get(*env, "OLDPWD"))
		return (ft_env_set(env, "OLDPWD", NULL));
	return (0);
}

int env_refresh(char ***env)
{
	if (set_shell_vars(env) == -1)
		return (-1);
	if (init_oldpwd(env) == -1)
		return (-1);
	return (0);
}
