/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols_get64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:10:37 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/18 19:48:20 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int8_t	symbol_get64(t_file_data *file, struct nlist_64 *sym)
{
	t_symbol_data	*new_symbol;
	char			*name;
	uint32_t		n_strx;
	int8_t			ret;

	n_strx = endian_wrap_32(sym->n_un.n_strx, file->endian);
	name = file->sym_str + n_strx;
	if (is_secure_str(file->content, file->size, name) == FALSE)
		return (print_corrupted_file_error(file->name));
	if (!(new_symbol = (t_symbol_data*)malloc(sizeof(*new_symbol))))
		return (print_malloc_error());
	ft_bzero(new_symbol, sizeof(*new_symbol));
	if (!(new_symbol->name = ft_strdup((n_strx) ? name : "")))
	{
		free(new_symbol);
		return (print_malloc_error());
	}
	new_symbol->value = endian_wrap_64(sym->n_value, file->endian); // !! 32 pour symbol_get_32 !!
	new_symbol->type = endian_wrap_32(sym->n_type, file->endian) & N_TYPE;
	new_symbol->ext = endian_wrap_32(sym->n_type, file->endian) & N_EXT;
	symbol_get_section(file, new_symbol, sym->n_sect);
	ret = symbol_to_tree(&file->symbols, new_symbol);
	if (ret == MALLOC_ERROR)
		free_symbol_data(new_symbol);
	return (ret ? ERROR : SUCCESS);
}

int8_t			symbols_get64(t_file_data *file)
{
	struct symtab_command	*sym_cmd;
	struct nlist_64			*sym_tab;
	uint32_t				i;
	uint32_t				nsyms;
	uint32_t				symoff;

	if (is_inside_file_rel(file->size, file->off_symtab, sizeof(*sym_cmd)) == FALSE)
		return (print_corrupted_file_error(file->name));
	sym_cmd = (struct symtab_command*)(file->content + file->off_symtab);
	nsyms = endian_wrap_32(sym_cmd->nsyms, file->endian);
	symoff = endian_wrap_32(sym_cmd->symoff, file->endian);
	if (is_inside_file_rel(file->size, symoff, sizeof(*sym_tab) * nsyms) == FALSE)
		return (print_corrupted_file_error(file->name));
	sym_tab = (struct nlist_64*)(file->content + symoff);
	file->sym_str = (char*)file->content + endian_wrap_32(sym_cmd->stroff, file->endian);
	i = 0;
	while (i < nsyms)
	{
		if (symbol_get64(file, &sym_tab[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
