/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bad_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:11:57 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/25 19:56:31 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	*get_error(int err)
{
	static t_error	tab[NB_ERRORS] = 
	{
		{ENOENT, "No such file or directory"},
		{EACCES, "Permission denied"},
		{EINVAL, "Invalid argument"},
		{ENOTDIR, "Not a directory"}
	};
	int				i;

	i = -1;
	while (++i < NB_ERRORS)
		if (tab[i].nb == err)
			return (tab[i].message);
	return ("Unknown reason");
}

int8_t	print_loading_file_error(char *file_name)
{
	int	err;

	err = errno;
	ft_putstr_fd("ft_nm: error: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(get_error(err), 2);
	ft_putstr_fd(".\n", 2);
	return (ERROR);
}

int8_t	print_invalid_file_error(t_file_data *file)
{
	ft_putstr_fd("ft_nm: error: ", 2);
	ft_putstr_fd(file->name, 2);
	if (file->arch)
	{
		ft_putstr_fd(" (for achitecture ", 2);
		ft_putstr_fd(file->arch, 2);
		ft_putstr_fd(")", 2);
	}
	ft_putstr_fd(" The file was not recognized as a valid object file\n", 2);
	return (ERROR);
}

int8_t	print_corrupted_file_error(t_file_data *file)
{
	ft_putstr_fd("ft_nm: error: ", 2);
	ft_putstr_fd(file->name, 2);
	if (file->arch)
	{
		ft_putstr_fd(" (for architecture ", 2);
		ft_putstr_fd(file->arch, 2);
		ft_putstr_fd(") ", 2);
	}
	ft_putstr_fd(" truncated or malformed object\n", 2);
	return (ERROR);
}
