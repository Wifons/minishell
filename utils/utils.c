/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:32:45 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:13:16 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clean(t_token *tokens)
{
	t_token	*tmp;
	if (tokens)
	{
		while (tokens)
			{
				tmp = tokens;
				tokens = tokens->next;
				free(tmp->value);
				free(tmp);
			}
	}
}
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("[%d : %s ]\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}
void	ft_print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}

/* Fonction chatgpt pour print temporairement a retirer plus tard */
void print_cmd(t_cmd *cmd)
{
    // Si la commande est vide, on ne l'affiche pas
    if (!cmd)
        return;

    // Affichage des arguments de la commande
    int i = 0;
    while (cmd->arguments && cmd->arguments[i])
    {
        printf("%s ", cmd->arguments[i]);
        i++;
    }

    // Affichage des redirections
    if (cmd->l_redirect)
        printf("< %s ", cmd->l_redirect);  // Redirection en entrée
    if (cmd->r_redirect)
        printf("> %s ", cmd->r_redirect);  // Redirection en sortie
    if (cmd->app_redirect)
        printf(">> %s ", cmd->app_redirect);  // Redirection en ajout (append)

    // Affichage du pipe suivant ou précédent
    if (cmd->next_pipe)
        printf("| ");
    
    // Si la commande a un pipe suivant, on continue avec la commande suivante
    printf("\n");
    if (cmd->next)
    {
        
        print_cmd(cmd->next);
    }
}