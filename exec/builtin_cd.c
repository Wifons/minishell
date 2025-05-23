#include "../minishell.h"

/*
** BUILTIN_CD - Change le répertoire de travail
**
** RÈGLES :
** - Sans argument : aller au répertoire HOME
** - Avec argument : aller au répertoire spécifié
** - Gérer les erreurs (répertoire inexistant)
**
** ÉTAPES :
** 1. Si pas d'argument, path = $HOME
** 2. Sinon, path = args[1]
** 3. Appeler chdir(path)
** 4. Si erreur, afficher message d'erreur
**
** EXEMPLES :
** cd        → va dans $HOME
** cd /tmp   → va dans /tmp
** cd bad    → "cd: bad: No such file or directory"
**
** CODES DE RETOUR :
** 0 = succès, 1 = erreur
*/
int builtin_cd(char **args)
{
	char	*path;

	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("Minishell : cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		printf("Minishell : cd: ");
		printf("%s", path);
		printf(": No such file or directory\n");
		return (1);
	}
	return (0);
}