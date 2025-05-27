/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:43:48 by toto              #+#    #+#             */
/*   Updated: 2025/01/22 02:59:02 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_stash
{
	char			*content;
	struct s_stash	*next;
}				t_stash;

int		ft_lstsize_gn(t_stash *lst);
//Main
char	*get_next_line(int fd);
t_stash	**ft_stash(t_stash **stash);
char	*ft_create_line(t_stash *stash);
void	ft_read(int fd, t_stash **stash);
int		ft_verif_newline(t_stash *stash);
//Utils
void	ft_lstadd_back_gn(t_stash **lst, t_stash *new);
t_stash	*ft_lstnew_gn(void *content);
t_stash	*ft_lstlast_gn(t_stash *lst);
void	ft_lstclear_gn(t_stash **lst);
int		ft_count_lst_gn(t_stash *lst);
#endif