/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:10:37 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/15 19:54:47 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

// CHANGE THE NAME OF THE FILE

int8_t	symbol_to_tree(t_options *options, t_btree **head, t_symbol_data *symbol)
{
	t_btree	*new;

	if (!(new = (t_btree*)malloc(sizeof(*new))))
		return (print_malloc_error());
	new->data = symbol;
	ft_btree_insert(head, new, symbol_get_sort_fun(options));
	return (SUCCESS);
}

int8_t	symbol_add(t_options *options, t_file_data *file, struct nlist_64 *sym)
{
	t_symbol_data	*new_symbol;
	char			*name;

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
	// if (symbol_get_section() == ERROR
	// 	|| symbol_to_tree(options, &file->symbols, new_symbol) = MALLOC_ERROR)
	// 	{
	// 		free_symbol(new_symbol);
	// 		return (ERROR);
	// 	}
	return (symbol_to_tree(options, &file->symbols, new_symbol));
}

int8_t	symbols_get_each64(t_options *options, t_file_data *file)
{
	struct symtab_command	*sym_cmd;
	struct nlist_64			*sym_tab;
	uint32_t				i;
	uint32_t				nsyms;

	if (is_inside_file_rel(file->size, file->off, sizeof(*sym_cmd)) == FALSE)
		return (print_corrupted_file_error(file->name));
	sym_cmd = (struct symtab_command*)(file->content + file->off);
	nsyms = sym_cmd->nsyms;
	if (is_inside_file_rel(file->size, sym_cmd->symoff, sizeof(*sym_tab) * nsyms) == FALSE)
		return (print_corrupted_file_error(file->name));
	sym_tab = (struct nlist_64*)(file->content + sym_cmd->symoff);
	file->sym_str = (char*)file->content + sym_cmd->stroff;
	i = 0;
	while (i < nsyms)
	{
		if (symbol_add(options, file, &sym_tab[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int8_t	symbols_get_symtab_cmd_off(t_file_data *file, uint32_t ncmds)
{
	uint32_t			i;
	struct load_command	*lc;	
	
	i = 0;
	while (i < ncmds)
	{
		if (is_inside_file_rel(file->size, file->off, sizeof(*lc)) == FALSE)
			return (print_corrupted_file_error(file->name));
		lc = (struct load_command*)(file->content + file->off);
		if (lc->cmd == LC_SYMTAB)
			return (SUCCESS);
		file->off += lc->cmdsize;
		i++;
	}
	return (print_corrupted_file_error(file->name));
}
