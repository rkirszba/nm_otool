/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols_get64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:10:37 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/16 17:52:50 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int8_t	symbol_get64(t_options *options, t_file_data *file, struct nlist_64 *sym)
{
	t_symbol_data	*new_symbol;
	char			*name;
	int8_t			ret;

	name = file->sym_str + sym->n_un.n_strx;
	if (is_secure_str(file->content, file->size, name) == FALSE)
		return (print_corrupted_file_error(file->name));
	if (!(new_symbol = (t_symbol_data*)malloc(sizeof(*new_symbol))))
		return (print_malloc_error());
	if (!(new_symbol->name = ft_strdup((sym->n_un.n_strx) ? name : "")))
	{
		free(new_symbol);
		return (print_malloc_error());
	}
	new_symbol->value = sym->n_value;
	new_symbol->type = sym->n_type & N_TYPE;
	new_symbol->ext = sym->n_type & N_EXT;
	symbol_get_section(file, new_symbol, sym->n_sect);
	ret = symbol_to_tree(options, &file->symbols, new_symbol);
	if (ret == MALLOC_ERROR)
		free_symbol_data(new_symbol);
	return (ret ? ERROR : SUCCESS);
}

int8_t			symbols_get64(t_options *options, t_file_data *file)
{
	struct symtab_command	*sym_cmd;
	struct nlist_64			*sym_tab;
	uint32_t				i;
	uint32_t				nsyms;

	if (is_inside_file_rel(file->size, file->off_symtab, sizeof(*sym_cmd)) == FALSE)
		return (print_corrupted_file_error(file->name));
	sym_cmd = (struct symtab_command*)(file->content + file->off_symtab);
	nsyms = sym_cmd->nsyms;
	if (is_inside_file_rel(file->size, sym_cmd->symoff,
			sizeof(*sym_tab) * nsyms) == FALSE)
		return (print_corrupted_file_error(file->name));
	sym_tab = (struct nlist_64*)(file->content + sym_cmd->symoff);
	file->sym_str = (char*)file->content + sym_cmd->stroff;
	i = 0;
	while (i < nsyms)
	{
		if (symbol_get64(options, file, &sym_tab[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
