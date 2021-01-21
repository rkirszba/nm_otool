/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:30:48 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/21 16:58:06 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static uint8_t	symbol_allow_print(t_options *options, t_symbol_data *symbol)
{
	if (symbol->debug)
		return (FALSE);
	if (options->u && symbol->sect != N_UNDF)
		return FALSE;
	if (options->U && symbol->sect == N_UNDF)
		return FALSE;
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
		print_value(symbol, file->bits);
		print_type(symbol);
	}
	ft_putstr(symbol->name);
	if (symbol->type == N_INDR && symbol->ext == TRUE)
		print_indirect(symbol);
	write(1, "\n", 1);
}

void		symbols_print(t_file_data *file)
{
	t_options	*options;

	options = static_options();
	if (options->multi_input || file->arch)
		if (!file->fat || file->arch)
		{
			write(1, "\n", 1);
			ft_putstr(file->name);
			if (file->arch)
			{
				ft_putstr(" (for architecture ");
				ft_putstr(file->arch);
				write(1, ")", 1);
			}
			write(1, ":\n", 2);
		}
	*(static_file()) = file;
	if (options->r)
		ft_btree_inrorder(file->symbols, &symbol_print);
	else
		ft_btree_inorder(file->symbols, &symbol_print);
}
