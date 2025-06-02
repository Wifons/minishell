/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:42:38 by toto              #+#    #+#             */
/*   Updated: 2024/12/05 04:30:07 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
			ft_lstclear(stash);
			return ;
		}
		node = ft_lstnew(buffer);
		ft_lstadd_back(stash, node);
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
	line = malloc(sizeof(char) * (ft_count_lst(stash) + 1));
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
	tempnode = ft_lstlast((*stash));
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
	ft_lstclear(stash);
	tempnode = ft_lstnew(tmpstash);
	ft_lstadd_back(stash, tempnode);
	return (stash);
}

/*	Main function, manage other function and result	*/
char	*get_next_line(int fd)
{
	static t_stash	*stash[OPEN_MAX] = {NULL};
	char			*buffer;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0
		|| read(fd, &buffer, 0) < 0)
	{
		if (fd >= 0 && fd < OPEN_MAX)
			ft_lstclear(&stash[fd]);
		return (NULL);
	}
	ft_read(fd, &stash[fd]);
	if (!stash[fd])
		return (NULL);
	buffer = ft_create_line(stash[fd]);
	if ((buffer == NULL || buffer[0] == '\0'))
	{
		ft_lstclear(&stash[fd]);
		if (buffer[0] == '\0')
			return (free(buffer), buffer = NULL);
		return (NULL);
	}
	ft_stash(&stash[fd]);
	return (buffer);
}
