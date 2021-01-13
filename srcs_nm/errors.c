/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:29:11 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/13 19:44:35 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int8_t	print_malloc_error(void)
{
	ft_putstr_fd("nm: Malloc failed\n", 2);
	return (ERROR);
}

int8_t	print_options_error(char wrong_option)
{
	ft_putstr_fd("nm: Unknown command line argument '-", 2);
	write(2, &wrong_option, 1);
	ft_putstr_fd("'.\n", 2);
	return (ERROR);
}