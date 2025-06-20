#include "../../minishell.h"

static int change_dir(t_shell *sh, char *path)
{
	if (ft_strcmp(path, "-") == 0)
	{
		path = handle_oldpwd(sh);
		if (!path)
			return (-1);
	}
	if (chdir(path) == -1)
	{
		print_chdir_error(path);
		return (-1);
	}
	return (SUCCESS);
}

static char *get_home_path(t_env_var *env)
{
	char *path;

	path = env_get(env, "HOME");
	if (!path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (path);
}

// static int handle_empty_arg(t_shell *sh)
// {
// 	char *home_value;

// 	home_value = env_get(sh->env, "HOME");
// 	if (!home_value)
// 	{
// 		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
// 		return (1);
// 	}
// 	return (2);
// }

static int handle_cd_args(t_shell *sh, t_cmd *cmd, char **path)
{
	if (!cmd->arguments[1])
	{
		*path = get_home_path(sh->env);
		if (!*path)
			return (1);
		if ((*path)[0] == '\0')
			return (2);
	}
	else if (cmd->arguments[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDOUT_FILENO);
		return (1);
	}
    else if (!cmd->arguments[1][0])
    {
        *path = get_home_path(sh->env);
        if (!*path)
            return (1);
        if ((*path)[0] == '\0')
            return (2);
    }
    else
        *path = cmd->arguments[1];
    return (0);
		
}

int builtin_cd(t_shell *sh, t_cmd *cmd)
{
	char *path;
	int result;

	path = NULL;
	if (!cmd || !cmd->arguments)
		return (-1);
	result = handle_cd_args(sh, cmd, &path);
	if (result == 1)
		return (result);
	if (result == 2)
		return (SUCCESS);
	if (result == SUCCESS && path)
	{
		if (change_dir(sh, path) == SUCCESS)
		{
			update_pwd_vars(sh);
			return (SUCCESS);
		}
	}
	return (1);
}
