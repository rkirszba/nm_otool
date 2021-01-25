/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_various.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:29:11 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/25 15:45:51 by rkirszba         ###   ########.fr       */
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
	ft_putstr_fd("ft_nm: Unknown command line argument '-", 2);
	write(2, &wrong_option, 1);
	ft_putstr_fd("'.\n\n", 2);
	ft_putstr_fd("USAGE: ./ft_nm [options] <input files>\n\n", 2);
	ft_putstr_fd("OPTIONS:\n\n", 2);
	ft_putstr_fd("-g     Display only global (external) symbols.\n", 2);
	ft_putstr_fd("-j     Just display the symbol names \
	(no value or type).\n", 2);
	ft_putstr_fd("-n     Sort numerically rather than alphabetically.\n", 2);
	ft_putstr_fd("-o     Prepend file or archive element name \
	to each output line, rather than only once.\n", 2);
	ft_putstr_fd("-p     Don't sort; display in symbol-table order.\n", 2);
	ft_putstr_fd("-r     Sort in reverse order.\n", 2);
	ft_putstr_fd("-u     Display only undefined symbols.\n", 2);
	ft_putstr_fd("-U     Show only defined symbols.\n", 2);
	return (ERROR);
}
