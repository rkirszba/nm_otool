/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_various.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:42:31 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/25 15:52:44 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

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

int8_t	print_options_error(char wrong_option, char *flag)
{
	ft_putstr_fd("ft_otool: Unknown command char ", 2);
	write(2, &wrong_option, 1);
	ft_putstr_fd(" in flag ", 2);
	ft_putstr_fd(flag, 2);
	write(2, "\n\n", 2);
	return (print_usage());
}

int8_t	print_usage(void)
{
	ft_putstr_fd("Usage: ft_otool [-dt] <object file> ...\n", 2);
	ft_putstr_fd("        -d print the data section\n", 2);
	ft_putstr_fd("        -t print the text section\n", 2);
	return (ERROR);
}
