/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols_print_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:41:17 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/27 12:04:31 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		print_value(t_symbol_data *symbol, t_bits arch)
{
	uint64_t	value;
	uint8_t		type;

	value = symbol->value;
	type = symbol->type;
	if (((type == N_UNDF && value == 0)
		|| type == N_INDR
		|| type == N_PBUD)
		&& symbol->ext == TRUE)
	{
		ft_putstr("        ");
		if (arch == bits64)
			ft_putstr("        ");
	}
	else if (arch == bits32)
		print_hex(value, 8);
	else
		print_hex(value, 16);
	write(1, " ", 1);
}

static void	print_type_section(t_symbol_data *symbol)
{
	if (symbol->sect == text)
		write(1, symbol->ext == TRUE ? "T" : "t", 1);
	else if (symbol->sect == data)
		write(1, symbol->ext == TRUE ? "D" : "d", 1);
	else if (symbol->sect == bss)
		write(1, symbol->ext == TRUE ? "B" : "b", 1);
	else if (symbol->sect == other)
		write(1, symbol->ext == TRUE ? "S" : "s", 1);
	else
		write(1, "?", 1);
}

void		print_type(t_symbol_data *symbol)
{
	if (symbol->type == N_UNDF)
	{
		if (symbol->value == 0)
			write(1, symbol->ext == TRUE ? "U" : "?", 1);
		else
			write(1, symbol->ext == TRUE ? "C" : "?", 1);
	}
	else if (symbol->type == N_PBUD)
		write(1, symbol->ext == TRUE ? "U" : "?", 1);
	else if (symbol->type == N_ABS)
		write(1, symbol->ext == TRUE ? "A" : "a", 1);
	else if (symbol->type == N_SECT)
		print_type_section(symbol);
	else if (symbol->type == N_INDR)
		write(1, symbol->ext == TRUE ? "I" : "i", 1);
	else
		write(1, "?", 1);
	write(1, " ", 1);
}

void		print_indirect(t_symbol_data *symbol)
{
	ft_putstr(" (indirect for ");
	if (ft_strlen(symbol->name) == 1 && symbol->name[0] == 0x2)
		ft_putstr("?");
	else
		ft_putstr(symbol->name);
	write(1, ")", 1);
}

void		print_name(t_file_data *file)
{
	if (file->arch)
	{
		ft_putstr("(for architecture ");
		ft_putstr(file->arch);
		write(1, "):", 2);
	}
	ft_putstr(file->name);
	write(1, ": ", 2);
}
