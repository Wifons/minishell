/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:08:02 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:08:03 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Print error message for file operations */
static void	print_file_error(const char *file)
{
	ft_putstr_fd("Minishell : ", STDERR_FILENO);
	perror(file);
}

/* Open file for reading (< file) */
int	open_infile(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_file_error(file);
	return (fd);
}

/* Open file for writing (> file) or appending (>> file) */
int	open_outfile(const char *file, bool append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, FILE_PERMS);
	if (fd == -1)
		print_file_error(file);
	return (fd);
}
