/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:42:38 by toto              #+#    #+#             */
/*   Updated: 2025/01/22 02:59:34 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ---------------- -------------------
int	ft_verif_newline(t_stash *stash)
{
	int	i;

	i = 0;
	if (stash == NULL)
		return (0);
	while (stash)
	{
		i = 0;
		while (i < BUFFER_SIZE && stash->content[i] != '\0')
		{
			if (stash->content[i] == '\n')
				return (1);
			i++;
		}
		stash = stash->next;
	}
	return (0);
}

/*	Read the file fd a write on tje stash lst */
void	ft_read(int fd, t_stash **stash)
{
	char	*buffer;
	t_stash	*node;
	int		b_read;

	while (!ft_verif_newline(*stash))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (!b_read)
		{
			free(buffer);
			return ;
		}
		buffer[b_read] = '\0';
		if (buffer[0] == '\0')
		{
			free(buffer);
			ft_lstclear_gn(stash);
			return ;
		}
		node = ft_lstnew_gn(buffer);
		ft_lstadd_back_gn(stash, node);
	}
}

/*	Read stash lst and write on line if != '\n'*/
char	*ft_create_line(t_stash *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	line = malloc(sizeof(char) * (ft_count_lst_gn(stash) + 1));
	while (stash)
	{
		i = 0;
		while (stash->content[i] && stash->content[i] != '\n')
			line[j++] = stash->content[i++];
		if (stash->content[i] == '\n')
		{
			line[j] = '\n';
			line[++j] = '\0';
			return (line);
		}
		stash = stash->next;
	}
	line[j] = '\0';
	return (line);
}

t_stash	**ft_stash(t_stash **stash)
{
	t_stash	*tempnode;
	char	*tmpstash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmpstash = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmpstash)
		return (NULL);
	tempnode = ft_lstlast_gn((*stash));
	if (!tempnode || !tempnode->content)
	{
		free(tmpstash);
		return (NULL);
	}
	while (tempnode->content[i] != '\n' && tempnode->content[i])
		i++;
	while (tempnode->content[i] && tempnode->content[++i])
		tmpstash[j++] = tempnode->content[i];
	tmpstash[j] = '\0';
	ft_lstclear_gn(stash);
	tempnode = ft_lstnew_gn(tmpstash);
	ft_lstadd_back_gn(stash, tempnode);
	return (stash);
}

/*	Main function, manage other function and result	*/
char	*get_next_line(int fd)
{
	static t_stash	*stash = NULL;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &buffer, 0) < 0)
	{
		ft_lstclear_gn(&stash);
		return (NULL);
	}
	ft_read(fd, &stash);
	if (!stash)
		return (NULL);
	buffer = ft_create_line(stash);
	if ((buffer == NULL || buffer[0] == '\0'))
	{
		ft_lstclear_gn(&stash);
		if (buffer[0] == '\0')
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	ft_stash(&stash);
	return (buffer);
}
