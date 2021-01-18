/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:30:48 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/18 16:16:05 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_hex(uint64_t nb, uint32_t width)
{
	if (width == 0)
		return ;
	print_hex(nb / 16, width - 1);
	write(1, &HEX_BASE[nb % 16], 1);
}

static void	print_value(uint64_t value, uint8_t type, t_arch arch)
{
	if (type == N_UNDF) // voir si pas d'autre
	{
		ft_putstr("        ");
		if (arch == x64)
			ft_putstr("        ");
	}
	else if (arch == x32)
		print_hex(value, 8);
	else
		print_hex(value, 16);
	ft_putstr(" ");
}

static void	print_type(t_symbol_data *symbol)
{
	// a affiner !!
	if (symbol->type == N_UNDF)
		write(1, symbol->ext == TRUE ? "U" : "u", 1);
	if (symbol->type == N_ABS)
		write(1, symbol->ext == TRUE ? "A" : "a", 1);
	if (symbol->type == N_SECT)
	{
		if (symbol->sect == text)
			write(1, symbol->ext == TRUE ? "T" : "t", 1);
		if (symbol->sect == data)
			write(1, symbol->ext == TRUE ? "D" : "d", 1);
		if (symbol->sect == bss)
			write(1, symbol->ext == TRUE ? "B" : "b", 1);
		if (symbol->sect == other)
			write(1, symbol->ext == TRUE ? "S" : "s", 1);
	}
 	if (symbol->type == N_INDR)
	 	write(1, symbol->ext == TRUE ? "I" : "i", 1);
	write(1, " ", 1);
}

static uint8_t	symbol_allow_print(t_options *options, t_symbol_data *symbol)
{
	if (options->u && symbol->sect != N_UNDF)
		return FALSE;
	if (options->U && symbol->sect == N_UNDF)
		return FALSE;
	//mettre condition debuggeur
	if (options->g && symbol->ext == FALSE)
		return FALSE;
	return TRUE; 
}

static void	symbol_print(void *data)
{
	t_options		*options;
	t_file_data		*file;
	t_symbol_data	*symbol;

	options = static_options();
	file = *static_file();
	symbol = (t_symbol_data*)data;
	if (symbol_allow_print(options, symbol) == FALSE)
		return ;
	if (options->o)
	{
		ft_putstr(file->name);
		write(1, ": ", 2);
	}
	if (!options->j && !options->u)
	{
		print_value(symbol->value, symbol->type, file->arch);
		print_type(symbol);
	}
	ft_putstr(symbol->name);
	write(1, "\n", 1);
}

void		symbols_print(t_file_data *file)
{
	t_options	*options;

	options = static_options();
	if (options->multi_input)
	{
		write(1, "\n", 1);
		ft_putstr(file->name);
		write(1, ":\n", 2);
	}
	*(static_file()) = file;
	if (options->r)
		ft_btree_inrorder(file->symbols, &symbol_print);
	else
		ft_btree_inorder(file->symbols, &symbol_print);
}