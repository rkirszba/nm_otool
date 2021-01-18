/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols_get_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:36:56 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/18 17:22:37 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int8_t	symbol_to_tree(t_btree **head, t_symbol_data *symbol)
{
	t_btree	*new;

	if (!(new = (t_btree*)malloc(sizeof(*new))))
		return (print_malloc_error());
	ft_bzero(new, sizeof(*new));
	new->data = symbol;
	ft_btree_insert(head, new, symbol_get_sort_fun());
	return (SUCCESS);
}

void	symbol_get_section(t_file_data *file, t_symbol_data *symbol, uint8_t sect_nb)
{
	if (sect_nb == NO_SECT)
		symbol->sect = none;
	else if (sect_nb == file->text_nb)
		symbol->sect = text;
	else if (sect_nb == file->data_nb)
		symbol->sect = data;
	else if (sect_nb == file->bss_nb)
		symbol->sect = bss;
	else
		symbol->sect = other;
}
