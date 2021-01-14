/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:29:11 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/14 13:23:05 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int8_t	print_malloc_error(void)
{
	ft_putstr_fd("nm: malloc failed\n", 2);
	return (MALLOC_ERROR);
}

int8_t	print_munmap_error(void)
{
	ft_putstr_fd("nm: munmap failed\n", 2);
	return (MALLOC_ERROR);
}

int8_t	print_options_error(char wrong_option)
{
	ft_putstr_fd("nm: Unknown command line argument '-", 2);
	write(2, &wrong_option, 1);
	ft_putstr_fd("'.\n", 2);
	return (ERROR);
}

static char	*get_error(int err)
{
	static t_error	tab[NB_ERRORS] = 
	{
		{ENOENT, "No such file or directory"},
		{EACCES, "Permission denied"},
		{EINVAL, "Invalid argument"}
	};
	int				i;

	i = -1;
	while (++i < NB_ERRORS)
		if (tab[i].nb == err)
			return (tab[i].message);
	return ("Unknown reason");
}

int8_t	print_file_error(char *file_name)
{
	int	err;

	err = errno;
	ft_putstr_fd("nm: error: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(get_error(err), 2);
	ft_putstr_fd(".\n", 2);
	return (ERROR);
}
